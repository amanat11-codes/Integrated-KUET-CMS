#include <stdio.h>
#include <string.h>
#include <time.h>
#include "hallDetailsPage.h"
#include "utility.h"
#include "studentDashboard.h"

#if 0
static int validDate(const char *input, char *isoDate)
{
    int day, month, year;
    char extra;

    if (strlen(input) != 10 ||
        input[2] != '-' || input[5] != '-')
    {
        return 0;
    }

    if (sscanf(input, "%d-%d-%d%c",
               &day, &month, &year, &extra) != 3)
    {
        return 0;
    }

    if (year < 1900 || year > 9999)
        return 0;

    struct tm date = {0};

    date.tm_mday = day;
    date.tm_mon = month - 1;
    date.tm_year = year - 1900;
    date.tm_isdst = -1;

    if (mktime(&date) == (time_t)-1)
        return 0;

    /* Reject impossible dates such as 31-02-2027 */
    if (date.tm_mday != day ||
        date.tm_mon != month - 1 ||
        date.tm_year != year - 1900)
    {
        return 0;
    }

    snprintf(isoDate, 11, "%04d-%02d-%02d",
             year, month, day);

    return 1;
}

static void setMealOffPeriod(const char *student_id)
{
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;

    char startInput[30];
    char endInput[30];
    char startDate[11];
    char endDate[11];

    printf("\n========== SET MEAL OFF PERIOD ==========\n");
    printf("Date format: DD-MM-YYYY\n");

    printf("Enter start date: ");

    if (scanf("%29s", startInput) != 1)
        return;

    printf("Enter end date: ");

    if (scanf("%29s", endInput) != 1)
        return;

    if (!validDate(startInput, startDate) ||
        !validDate(endInput, endDate))
    {
        printf("\nInvalid date! Use DD-MM-YYYY.\n");
        return;
    }

    if (strcmp(startDate, endDate) > 0)
    {
        printf("\nEnd date must not be before start date.\n");
        return;
    }

    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK)
    {
        printf("Database error: %s\n",
               db ? sqlite3_errmsg(db) : "Unknown error");

        if (db != NULL)
            sqlite3_close(db);

        return;
    }

    const char *sql =
        "INSERT INTO meal_off_periods "
        "(student_id, start_date, end_date) "
        "VALUES (?, ?, ?)";

    if (sqlite3_prepare_v2(
            db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("SQL error: %s\n", sqlite3_errmsg(db));

        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(
        stmt, 1, student_id, -1, SQLITE_TRANSIENT);

    sqlite3_bind_text(
        stmt, 2, startDate, -1, SQLITE_TRANSIENT);

    sqlite3_bind_text(
        stmt, 3, endDate, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        printf("\nMeal Off Period saved successfully!\n");
        printf("Start date: %s\n", startInput);
        printf("End date:   %s\n", endInput);
    }
    else
    {
        printf("Could not save Meal Off Period: %s\n",
               sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

static void viewMealOffPeriods(const char *student_id)
{
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;

    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK)
    {
        printf("Database error: %s\n",
               db ? sqlite3_errmsg(db) : "Unknown error");

        if (db != NULL)
            sqlite3_close(db);

        return;
    }

    const char *sql =
        "SELECT start_date, end_date "
        "FROM meal_off_periods "
        "WHERE student_id = ? "
        "ORDER BY start_date";

    if (sqlite3_prepare_v2(
            db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("SQL error: %s\n", sqlite3_errmsg(db));

        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(
        stmt, 1, student_id, -1, SQLITE_TRANSIENT);

    printf("\n========== YOUR MEAL OFF PERIODS ==========\n");

    int rc;
    int count = 0;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        const char *startDate =
            (const char *)sqlite3_column_text(stmt, 0);

        const char *endDate =
            (const char *)sqlite3_column_text(stmt, 1);

        int sd, sm, sy, ed, em, ey;

        if (sscanf(startDate, "%d-%d-%d",
                   &sy, &sm, &sd) == 3 &&
            sscanf(endDate, "%d-%d-%d",
                   &ey, &em, &ed) == 3)
        {
            printf("%d. %02d-%02d-%04d to %02d-%02d-%04d\n",
                   ++count, sd, sm, sy, ed, em, ey);
        }
    }

    if (rc != SQLITE_DONE)
    {
        printf("Could not retrieve periods: %s\n",
               sqlite3_errmsg(db));
    }
    else if (count == 0)
    {
        printf("No Meal Off Periods found.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
#endif

void showHallDetails(HallDetails *record, const char *student_id)
{
    char nextFeastDate[11];
    showDate(record->nextMonthlyFeast, nextFeastDate);
    printf("Student ID             %s\n", student_id);
    printf("Hall Name              %s\n", record->hallName);
    printf("Meal Status            %d\n", record->mealStatus);
    printf("Boarder                %d\t\tSide:     %s\n", record->boarderNumber, record->hallSide);
    printf("Next Monthly Feast     %s\n", nextFeastDate);
}

/*
typedef struct {
    char hallName[50];
    int mealStatus;
    int boarderNumber;
    char hallSide[10];
    Date nextMonthlyFeast;
    int setMeal;
} HallDetails;
*/



void hallDetailsPage(const char *student_id, const char *filepath)
{
    clearScreen();
    printBoxedText("HALL DETAILS PAGE");


    
    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL)
    {
        printf("Error opening file: %s\n", filepath);
        getCharacter("Press ENTER to return to the student dashboard...");
        return;
    }

    HallDetails record;
    StudentFileHeader header;

    fread(&header, sizeof(StudentFileHeader), 1, fp);
    fseek(fp, header.hallDetailsOffset, SEEK_SET);

    if (fread(&record, sizeof(HallDetails), 1, fp) != 1)
    {
        printf("Error reading file: %s\n", filepath);
        fclose(fp);
        getCharacter("Press ENTER to return to the student dashboard...");
        return;
    }
    fclose(fp);

    showHallDetails(&record, student_id);
    


    getCharacter("Press ENTER to return to the student dashboard...");

}
