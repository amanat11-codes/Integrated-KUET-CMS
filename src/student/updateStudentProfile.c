#include <stdio.h>
#include <string.h>

#include "studentDashboard.h"
#include "updateStudentProfile.h"
#include "utility.h"

static int confirmValue(const char *field, const char *value)
{
    char response;

    printf("%s: %s\n", field, value);
    response = getCharacter("  [?] Save this value? (Y/N): ");
    return response == 'Y' || response == 'y';
}

static void updateStringField(const char *field, char *destination, size_t size)
{
    char value[160];

    while (1)
    {
        char prompt[192];
        snprintf(prompt, sizeof(prompt), "[?] Enter new %s: ", field);
        getString(prompt, (int)sizeof(value), value);
        if (value[0] == '\0')
        {
            char ch = getCharacter("[!] Empty input. \n[?] Enter [y] to try again or [n] to keep the current value: ");
            if (ch == 'n' || ch == 'N')
                return;
            if (ch == 'y' || ch == 'Y')
                continue;
            printf("[!] Invalid option. Please enter y or n.\n");
            continue;
        }
        if (confirmValue(field, value))
        {
            strncpy(destination, value, size - 1);
            destination[size - 1] = '\0';
            return;
        }
    }
}

static void updateIntField(const char *field, int *destination)
{
    while (1)
    {
        char value[32];
        int number = getInt("[?] Enter new value: ");
        snprintf(value, sizeof(value), "%d", number);
        if (confirmValue(field, value))
        {
            *destination = number;
            return;
        }
    }
}

static int parseDateText(const char *text, Date *date)
{
    int day;
    int month;
    int year;
    char extra;

    if (sscanf(text, "%2d-%2d-%4d%c", &day, &month, &year, &extra) != 3 ||
        day < 1 || day > 31 || month < 1 || month > 12 ||
        year < 1900 || year > 9999)
        return 0;

    date->day = day;
    date->month = month;
    date->year = year;
    return 1;
}

static void updateDateField(const char *field, Date *destination)
{
    char value[32];
    char today[11];

    while (1)
    {
        getString("[?] Enter date (dd-mm-yyyy; leave blank for today's date): ",
                  sizeof(value), value);
        if (value[0] == '\0' && getTodayDateString(today, sizeof(today)))
            strcpy(value, today);

        Date date;
        if (parseDateText(value, &date) && confirmValue(field, value))
        {
            *destination = date;
            return;
        }
        printf("[!] Invalid date. Please use dd-mm-yyyy.\n");
    }
}

static void updateDateStringField(const char *field, char *destination, size_t size)
{
    char value[32];
    char today[11];
    Date date;

    while (1)
    {
        getString("[?] Enter date (dd-mm-yyyy; leave blank for today's date): ",
                  sizeof(value), value);
        if (value[0] == '\0' && getTodayDateString(today, sizeof(today)))
            strcpy(value, today);

        if (parseDateText(value, &date) && confirmValue(field, value))
        {
            strncpy(destination, value, size - 1);
            destination[size - 1] = '\0';
            return;
        }
        printf("[!] Invalid date. Please use dd-mm-yyyy.\n");
    }
}

static int readStudentData(const char *filepath,
                           StudentFileHeader *header,
                           StudentProfile *profile,
                           AcademicRecord *academic,
                           HallDetails *hall,
                           LibraryDetails *library)
{
    FILE *file = fopen(filepath, "rb");
    if (file == NULL ||
        fread(header, sizeof(*header), 1, file) != 1 ||
        fseek(file, (long)header->studentProfileOffset, SEEK_SET) != 0 ||
        fread(profile, sizeof(*profile), 1, file) != 1 ||
        fseek(file, (long)header->academicRecordOffset, SEEK_SET) != 0 ||
        fread(academic, sizeof(*academic), 1, file) != 1 ||
        fseek(file, (long)header->hallDetailsOffset, SEEK_SET) != 0 ||
        fread(hall, sizeof(*hall), 1, file) != 1 ||
        fseek(file, (long)header->libraryDetailsOffset, SEEK_SET) != 0 ||
        fread(library, sizeof(*library), 1, file) != 1)
    {
        if (file != NULL)
            fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}

static int writeStudentData(const char *filepath,
                            const StudentFileHeader *header,
                            const StudentProfile *profile,
                            const AcademicRecord *academic,
                            const HallDetails *hall,
                            const LibraryDetails *library)
{
    FILE *file = fopen(filepath, "rb+");
    if (file == NULL ||
        fseek(file, (long)header->studentProfileOffset, SEEK_SET) != 0 ||
        fwrite(profile, sizeof(*profile), 1, file) != 1 ||
        fseek(file, (long)header->academicRecordOffset, SEEK_SET) != 0 ||
        fwrite(academic, sizeof(*academic), 1, file) != 1 ||
        fseek(file, (long)header->hallDetailsOffset, SEEK_SET) != 0 ||
        fwrite(hall, sizeof(*hall), 1, file) != 1 ||
        fseek(file, (long)header->libraryDetailsOffset, SEEK_SET) != 0 ||
        fwrite(library, sizeof(*library), 1, file) != 1 ||
        fflush(file) != 0)
    {
        if (file != NULL)
            fclose(file);
        return 0;
    }

    return fclose(file) == 0;
}

void updateStudentProfile(const char *student_id, const char *filepath)
{
    StudentFileHeader header;
    StudentProfile profile;
    AcademicRecord academic;
    HallDetails hall;
    LibraryDetails library;

    (void)student_id;
    clearScreen();
    printBoxedText("UPDATE STUDENT PROFILE");

    if (!readStudentData(filepath, &header, &profile, &academic, &hall, &library))
    {
        printf("[!] Error reading student data: %s\n", filepath);
        getCharacter("[?] Press ENTER to return to the student dashboard...");
        return;
    }

    while (1)
    {
        clearScreen();
        printMenuItems(4, "Profile", "Academic", "Hall", "Library");
        printf("0. Save and Exit\n");

        int choice = getInt("[?] Select section to update: ");
        while (getchar() != '\n')
            ; // Clear the input buffer
        if (choice == 0)
            break;

        if (choice == 1)
        {
            clearScreen();
            printMenuItems(12, "Name", "Department", "Year", "Term", "Phone", "Email",
                           "Blood Group", "Father's Name", "Mother's Name",
                           "Permanent Address", "Current Address", "Advisor");
            printf("0. Save and Exit\n");

            int field = getInt("[?] Select profile field to update: ");
            while (getchar() != '\n')
                ; // Clear the input buffer
            switch (field)
            {
            case 1:
                updateStringField("name", profile.name, sizeof(profile.name));
                break;
            case 2:
                updateStringField("department", profile.department, sizeof(profile.department));
                break;
            case 3:
                updateStringField("year", profile.year, sizeof(profile.year));
                break;
            case 4:
                updateStringField("term", profile.term, sizeof(profile.term));
                break;
            case 5:
                updateStringField("phone", profile.phone, sizeof(profile.phone));
                break;
            case 6:
                while (1)
                {
                    char email[sizeof(profile.email)];
                    getString("[?] Enter new email: ", sizeof(email), email);
                    if (validateEmailFormat(email, STUDENT) == 0 &&
                        confirmValue("email", email))
                    {
                        strcpy(profile.email, email);
                        break;
                    }
                }
                break;
            case 7:
                updateStringField("blood group", profile.bloodGroup, sizeof(profile.bloodGroup));
                break;
            case 8:
                updateStringField("father's name", profile.fathersName, sizeof(profile.fathersName));
                break;
            case 9:
                updateStringField("mother's name", profile.mothersName, sizeof(profile.mothersName));
                break;
            case 10:
                updateStringField("permanent address", profile.permanentAddress, sizeof(profile.permanentAddress));
                break;
            case 11:
                updateStringField("current address", profile.currentAddress, sizeof(profile.currentAddress));
                break;
            case 12:
                updateStringField("advisor", profile.advisor, sizeof(profile.advisor));
                break;
            default:
                break;
            }
        }
        else if (choice == 2)
        {
            clearScreen();

            printMenuItems(3, "Session", "Year", "Term");
            printf("0. Save and Exit\n");
            int field = getInt("[?] Select academic field to update: ");
            while (getchar() != '\n')
                ; // Clear the input buffer
            switch (field)
            {
            case 1:
                updateIntField("session", &academic.session);
                break;
            case 2:
                updateIntField("academic year", &academic.year);
                break;
            case 3:
                updateIntField("academic term", &academic.term);
                break;
            default:
                break;
            }
        }
        else if (choice == 3)
        {
            clearScreen();

            printMenuItems(8, "Hall Name", "Meal Status", "Boarder Number", "Hall Side",
                           "Next Monthly Feast", "Set Meal", "Meal OFF Start Date", "Meal OFF End Date");
            printf("0. Save and Exit\n");
            int field = getInt("[?] Select hall field to update: ");
            while (getchar() != '\n')
                ; // Clear the input buffer
            switch (field)
            {
            case 1:
                updateStringField("hall name", hall.hallName, sizeof(hall.hallName));
                break;
            case 2:
                updateIntField("meal status", &hall.mealStatus);
                break;
            case 3:
                updateIntField("boarder number", &hall.boarderNumber);
                break;
            case 4:
                updateStringField("hall side", hall.hallSide, sizeof(hall.hallSide));
                break;
            case 5:
                updateDateField("next monthly feast", &hall.nextMonthlyFeast);
                break;
            case 6:
                updateIntField("set meal", &hall.setMeal);
                break;
            case 7:
                updateDateStringField("Meal OFF start date", hall.offStartDate, sizeof(hall.offStartDate));
                break;
            case 8:
                updateDateStringField("Meal OFF end date", hall.offEndDate, sizeof(hall.offEndDate));
                break;
            default:
                break;
            }
        }
        else if (choice == 4)
        {
            clearScreen();

            int book = getInt("[?] Library book number (1-3, 0-Back): ");
            if (book >= 1 && book <= 3)
            {
                clearScreen();

                printMenuItems(2, "Book Title", "Return Date");
                printf("0. Back\n");
                int field = getInt("[?] Select library field to update: ");
                while (getchar() != '\n')
                    ; // Clear the input buffer
                if (field == 1)
                    updateStringField("book title", library.books[book - 1].bookTitle,
                                      sizeof(library.books[book - 1].bookTitle));
                else if (field == 2)
                    updateDateField("book return date", &library.books[book - 1].returnDate);
            }
        }
        else
        {
            printf("[!] Invalid section. Please try again.\n");
        }
    }

    if (writeStudentData(filepath, &header, &profile, &academic, &hall, &library))
        printf("Student information updated successfully.\n");
    else
        printf("[!] Error writing updated student information: %s\n", filepath);

    getCharacter("[?] Press ENTER to return to the student dashboard...");
}
