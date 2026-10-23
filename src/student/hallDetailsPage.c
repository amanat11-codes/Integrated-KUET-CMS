
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hallDetailsPage.h"
#include "utility.h"
#include "studentDashboard.h"

static int isLeapYear(int year)
{
    return (year % 400 == 0) ||
           (year % 4 == 0 && year % 100 != 0);
}

static int daysInMonth(int month, int year)
{
    const int days[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (month < 1 || month > 12)
        return 0;

    if (month == 2 && isLeapYear(year))
        return 29;

    return days[month - 1];
}

/* Strictly validates DD-MM-YYYY. */
static int parseDate(const char *input, struct tm *result)
{
    int day, month, year;
    char extra;

    if (input == NULL || strlen(input) != 10)
        return 0;

    if (input[2] != '-' || input[5] != '-')
        return 0;

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5)
            continue;

        if (input[i] < '0' || input[i] > '9')
            return 0;
    }

    if (sscanf(input, "%2d-%2d-%4d%c",
               &day, &month, &year, &extra) != 3)
        return 0;

    if (year < 1900 || year > 9999)
        return 0;

    if (month < 1 || month > 12)
        return 0;

    if (day < 1 || day > daysInMonth(month, year))
        return 0;

    if (result != NULL) {
        memset(result, 0, sizeof(*result));

        result->tm_mday = day;
        result->tm_mon = month - 1;
        result->tm_year = year - 1900;
        result->tm_hour = 12;
        result->tm_isdst = -1;
    }

    return 1;
}

static time_t dateToTime(const char *date)
{
    struct tm parsed;

    if (!parseDate(date, &parsed))
        return (time_t)-1;

    return mktime(&parsed);
}

/* Returns today's date at noon in local time. */
static time_t getToday(void)
{
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    if (local == NULL)
        return (time_t)-1;

    struct tm today = *local;

    today.tm_hour = 12;
    today.tm_min = 0;
    today.tm_sec = 0;
    today.tm_isdst = -1;

    return mktime(&today);
}

static int validateMealOffDates(
    const char *startDate,
    const char *endDate)
{
    struct tm parsedStart;
    struct tm parsedEnd;

    if (!parseDate(startDate, &parsedStart)) {
        printf("\n[!] [ERROR] Invalid start date: %s\n", startDate);
        printf("Use a valid DD-MM-YYYY date.\n");
        return 0;
    }

    if (!parseDate(endDate, &parsedEnd)) {
        printf("\n[!] [ERROR] Invalid end date: %s\n", endDate);
        printf("Use a valid DD-MM-YYYY date.\n");
        return 0;
    }

    time_t start = mktime(&parsedStart);
    time_t end = mktime(&parsedEnd);
    time_t today = getToday();
    if (start == (time_t)-1 ||
        end == (time_t)-1 ||
        today == (time_t)-1) {
        printf("\n[!] [ERROR] Could not validate the dates.\n");
        return 0;
    }
    if (start <= today) {
        printf("\n[!] [ERROR] Meal OFF must start from tomorrow onwards.\n");
        return 0;
    }

    if (end < start) {
        printf("\n[!] [ERROR] End date cannot be before start date.\n");
        return 0;
    }
    return 1;
}

/* =====================================================
   2. SAFE CONSOLE INPUT
   ===================================================== */

static int readLine(
    const char *prompt,
    char *buffer,
    size_t size)
{
    printf("%s", prompt);

    if (fgets(buffer, (int)size, stdin) == NULL)
        return 0;

    char *newline = strchr(buffer, '\n');

    if (newline != NULL) {
        *newline = '\0';
    } else {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;

            printf("\n[!] [ERROR] Input is too long.\n");
            return 0;
        }
    }

    size_t len = strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\r')
        buffer[len - 1] = '\0';

    return 1;
}

static int readMenuChoice(int *choice)
{
    char input[32];
    char *end;

    if (!readLine("[?] Enter your choice: ", input, sizeof(input)))
        return 0;

    long value = strtol(input, &end, 10);

    while (*end == ' ' || *end == '\t')
        end++;

    if (end == input || *end != '\0' ||
        value < 1 || value > 3)
        return 0;

    *choice = (int)value;
    return 1;
}

/* =====================================================
   3. BINARY FILE READ
   ===================================================== */

static int readHallRecord(
    const char *filepath,
    StudentFileHeader *header,
    HallDetails *record)
{
    FILE *fp = fopen(filepath, "rb");

    if (fp == NULL) {
        printf("\n[!] [ERROR] Cannot open file: %s\n", filepath);
        return 0;
    }

    int success = 0;
    long fileSize;
    long offset;

    if (fseek(fp, 0, SEEK_END) != 0)
        goto cleanup;

    fileSize = ftell(fp);

    if (fileSize < 0 ||
        (unsigned long)fileSize < sizeof(*header))
        goto cleanup;

    if (fseek(fp, 0, SEEK_SET) != 0)
        goto cleanup;

    if (fread(header, sizeof(*header), 1, fp) != 1)
        goto cleanup;

    offset = (long)header->hallDetailsOffset;

    if (offset < 0 || offset > fileSize)
        goto cleanup;

    if (sizeof(*record) > (size_t)(fileSize - offset))
        goto cleanup;

    if (fseek(fp, offset, SEEK_SET) != 0)
        goto cleanup;

    if (fread(record, sizeof(*record), 1, fp) != 1)
        goto cleanup;

    success = 1;

cleanup:
    if (!success)
        printf("\n[!] [ERROR] Invalid or incomplete student data file.\n");

    fclose(fp);
    return success;
}

/* =====================================================
   4. BINARY FILE WRITE
   ===================================================== */

static int writeHallRecord(
    const char *filepath,
    const StudentFileHeader *header,
    const HallDetails *record)
{
    FILE *fp = fopen(filepath, "rb+");

    if (fp == NULL) {
        printf("\n[!] [ERROR] Cannot open file for updating.\n");
        return 0;
    }

    int success = 0;
    long fileSize;
    long offset = (long)header->hallDetailsOffset;

    if (fseek(fp, 0, SEEK_END) != 0)
        goto cleanup;

    fileSize = ftell(fp);

    if (fileSize < 0 ||
        offset < 0 ||
        offset > fileSize)
        goto cleanup;

    if (sizeof(*record) > (size_t)(fileSize - offset))
        goto cleanup;

    if (fseek(fp, offset, SEEK_SET) != 0)
        goto cleanup;

    if (fwrite(record, sizeof(*record), 1, fp) != 1)
        goto cleanup;

    if (fflush(fp) != 0)
        goto cleanup;

    success = 1;

cleanup:
    if (!success)
        printf("\n[!] [ERROR] Failed to save Hall Details.\n");

    if (fclose(fp) != 0)
        success = 0;

    return success;
}

/* =====================================================
   5. EFFECTIVE MEAL STATUS
   ===================================================== */

/*
 * Return:
 *  1 = Meal ON
 *  0 = Meal OFF
 * -1 = Invalid schedule or file error
 *
 * Expired schedules are cleared and saved.
 */

static int getEffectiveMealStatus(
    const char *filepath,
    StudentFileHeader *header,
    HallDetails *record)
{
    /* No scheduled OFF period. */
    if (record->offStartDate[0] == '\0' &&
        record->offEndDate[0] == '\0') {
        return record->mealStatus == 1 ? 1 : -1;
    }

    /* Both dates must be present. */
    if (record->offStartDate[0] == '\0' ||
        record->offEndDate[0] == '\0') {
        printf("\n[WARNING] Incomplete Meal OFF schedule.\n");
        return -1;
    }

    time_t today = getToday();
    time_t start = dateToTime(record->offStartDate);
    time_t end = dateToTime(record->offEndDate);

    if (today == (time_t)-1 ||
        start == (time_t)-1 ||
        end == (time_t)-1 ||
        end < start) {
        printf("\n[!] [WARNING] Invalid saved Meal OFF dates.\n");
        return -1;
    }

    /* Expired schedule: reset and persistently save ON. */
    if (today > end) {
        record->mealStatus = 1;
        record->offStartDate[0] = '\0';
        record->offEndDate[0] = '\0';

        if (!writeHallRecord(filepath, header, record))
            return -1;

        return 1;
    }

    /* Schedule has not started yet. */
    if (today < start)
        return 1;

    /* Start and end dates are both inclusive. */
    return 0;
}

/* =====================================================
   6. SET MEAL OFF PERIOD
   ===================================================== */

static void setMealOffPeriod(const char *filepath)
{
    char startDate[32];
    char endDate[32];
    char today[11];

    if (!getTodayDateString(today, sizeof(today))) {
        printf("\n[!] [ERROR] Could not determine today's date.\n");
        getCharacter("[?] \nPress ENTER to return...");
        return;
    }

    while (1) {
        clearScreen();
        printBoxedText("SET MEAL OFF PERIOD");

        printf("\nDate format: DD-MM-YYYY\n");
        printf("Enter 0 at either prompt to cancel.\n\n");

        if (!readLine("[?] Enter date (dd-mm-yyyy; leave blank for today's date): ",
                      startDate, sizeof(startDate)))
            continue;

        if (strcmp(startDate, "0") == 0)
            return;

        if (startDate[0] == '\0')
            strcpy(startDate, today);

        if (!readLine("[?] Enter date (dd-mm-yyyy; leave blank for today's date): ",
                      endDate, sizeof(endDate)))
            continue;

        if (strcmp(endDate, "0") == 0)
            return;

        if (endDate[0] == '\0')
            strcpy(endDate, today);

        if (!validateMealOffDates(startDate, endDate)) {
            getCharacter("[?] \nPress ENTER to try again...");
            continue;
        }

        StudentFileHeader header;
        HallDetails record;

        if (!readHallRecord(filepath, &header, &record)) {
            getCharacter("[?] \nPress ENTER to return...");
            return;
        }

        /*
         * Verify that date fields can store DD-MM-YYYY
         * plus the terminating null character.
         */
        if (sizeof(record.offStartDate) < 11 ||
            sizeof(record.offEndDate) < 11) {
            printf("\n[!] [ERROR] Date fields must have at least 11 bytes.\n");
            getCharacter("[?] \nPress ENTER to return...");
            return;
        }

        record.mealStatus = 0;

        strcpy(record.offStartDate, startDate);
        strcpy(record.offEndDate, endDate);

        if (writeHallRecord(filepath, &header, &record)) {
            printf("\n[SUCCESS] Meal OFF schedule saved.\n");
            printf("Meal OFF From  : %s\n", startDate);
            printf("Meal OFF Until : %s\n", endDate);
        }

        getCharacter("[?] \nPress ENTER to return...");
        return;
    }
}

/* =====================================================
   7. TURN MEAL ON
   ===================================================== */

static void turnOnMeal(const char *filepath)
{
    StudentFileHeader header;
    HallDetails record;

    if (!readHallRecord(filepath, &header, &record)) {
        getCharacter("[?] \nPress ENTER to return...");
        return;
    }

    record.mealStatus = 1;

    record.offStartDate[0] = '\0';
    record.offEndDate[0] = '\0';

    if (writeHallRecord(filepath, &header, &record))
        printf("\n[SUCCESS] Meal is now ON.\n");

    getCharacter("[?] \nPress ENTER to return...");
}

/* =====================================================
   8. DISPLAY HALL DETAILS
   ===================================================== */

static void showHallDetails(
    HallDetails *record,
    const char *student_id)
{
    char *nextFeastDate = "N/A";
    nextFeastDate = showDate(record->nextMonthlyFeast);

    time_t today = getToday();
    time_t start = dateToTime(record->offStartDate);
    time_t end = dateToTime(record->offEndDate);

    int hasStart = record->offStartDate[0] != '\0';
    int hasEnd = record->offEndDate[0] != '\0';

    printBoxedText("HALL INFORMATION DASHBOARD");

    printf("\n---------------------------------------------\n");
    printf("Student ID         : %s\n", student_id);
    printf("Hall Name          : %s\n", record->hallName);
    printf("Hall Side          : %s\n", record->hallSide);
    printf("Boarder Number     : %d\n", record->boarderNumber);

    if (!hasStart && !hasEnd) {
        printf("Meal Status        : %s\n",
               record->mealStatus == 1 ? "ON" : "UNKNOWN");

        printf("Meal OFF Period    : None\n");
    }
    else if (!hasStart || !hasEnd ||
             today == (time_t)-1 ||
             start == (time_t)-1 ||
             end == (time_t)-1 ||
             end < start) {
        printf("Meal Status        : UNKNOWN\n");
        printf("[!] Meal OFF Period    : Invalid saved schedule\n");
    }
    else {
        printf("Meal OFF From      : %s\n", record->offStartDate);
        printf("Meal OFF Until     : %s\n", record->offEndDate);

        if (today < start) {
            printf("Meal Status        : ON\n");
            printf("Schedule Status    : SCHEDULED\n");
            printf("Message            : Meal OFF has not started yet.\n");
        }
        else if (today <= end) {
            printf("Meal Status        : OFF\n");
            printf("Schedule Status    : CURRENTLY ACTIVE\n");
        }
        else {
            printf("Meal Status        : ON\n");
            printf("Schedule Status    : EXPIRED\n");
        }
    }

    printf("Next Monthly Feast : %s\n", nextFeastDate);
    printf("---------------------------------------------\n");
}

/* =====================================================
   9. MAIN HALL DETAILS PAGE
   ===================================================== */

void hallDetailsPage(
    const char *student_id,
    const char *filepath)
{
    int choice;

    if (student_id == NULL || filepath == NULL) {
        printf("\n[!] [ERROR] Missing student ID or file path.\n");
        return;
    }

    while (1) {
        clearScreen();

        StudentFileHeader header;
        HallDetails record;

        if (!readHallRecord(filepath, &header, &record)) {
            getCharacter("[?] \nPress ENTER to return to dashboard...");
            return;
        }

        /*
         * This also clears and saves expired schedules.
         */
        int status = getEffectiveMealStatus(
            filepath, &header, &record);

        /*
         * Do not claim a reliable status when schedule
         * validation or file update failed.
         */
        if (status == -1) {
            printf("\n[!] [WARNING] Meal status could not be verified.\n");
        } else {
            record.mealStatus = status;
        }

        showHallDetails(&record, student_id);

        printf("\nMenu:\n");
        printf("1. Set Meal OFF Period\n");
        printf("2. Turn Meal ON\n");
        printf("3. Back to Dashboard\n");

        if (!readMenuChoice(&choice)) {
            printf("\n[!] [ERROR] Enter a valid choice from 1 to 3.\n");
            getCharacter("[?] Press ENTER to continue...");
            continue;
        }

        switch (choice) {
            case 1:
                setMealOffPeriod(filepath);
                break;

            case 2:
                turnOnMeal(filepath);
                break;

            case 3:
                return;
        }
    }
}
