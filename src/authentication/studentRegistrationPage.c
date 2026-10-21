#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "studentRegistrationPage.h"
#include "studentDashboard.h"
#include "utility.h"

/* ---- Field size limits (max chars, excluding NUL) ---- */
#define ID_MAX_LENGTH 8
#define PASS_MAX_LENGTH 8

/* ---- Paths ---- */
#define CREDENTIALS_PATH "database/credentials.dat"
#define STUDENTS_DIR "database/students/"

/* ------------------------------------------------------------------
 * studentRegistrationPage
 * Collects student ID, password, and full profile; writes a record
 * to credentials.dat and creates database/students/ID.student.
 * ------------------------------------------------------------------ */
void studentRegistrationPage(void)
{
    char studentId[ID_MAX_LENGTH + 1];
    char password[PASS_MAX_LENGTH + 1];
    char confirmPass[PASS_MAX_LENGTH + 1];

    /* ---- Profile fields ---- */
    StudentProfile profile;
    memset(&profile, 0, sizeof(profile));

    clearScreen();

    printf("\n");
    printf("================================================================\n");
    printf("                   STUDENT REGISTRATION                         \n");
    printf("================================================================\n");
    printf("\n");

    /* ---- Step 1: Student ID ---- */
    printf("  Step 1 of 3: Account Credentials\n");
    printf("----------------------------------------------------------------\n");
    printf("\n");
    printf("  Student ID must be %d characters.\n",
           ID_MAX_LENGTH);
    printf("\n");

    while (1)
    {
        getString("  Enter Student ID (first 8 digits are taken): ", sizeof(studentId), studentId);

        if (studentId[0] == '\0' || isAllDigits(studentId) == 0)
        {
            printf("  [!] Student ID must contain only digits and cannot be empty. Try again.\n\n");
            continue;
        }

        if (isIdAlreadyRegistered(studentId))
        {
            printf("  [!] This ID is already registered. Please use a different ID.\n\n");
            continue;
        }

        printf("  [?] Student ID: %s\n", studentId);
        char ch = getCharacter("      Are you sure you want to use this ID? (Y/N): ");

        if (ch == 'Y' || ch == 'y')
            break;
        else
        {
            printf("  [!] Please enter a different Student ID.\n\n");
            continue;
        }
    }

    /* ---- Step 2: Password (confirmed) ---- */
    printf("\n");
    printf("  Password must be %d characters.\n", PASS_MAX_LENGTH);
    printf("\n");

    while (1)
    {
        getString("  Enter Password (first 8 characters are taken): ", sizeof(password), password);

        if (password[0] == '\0' || isAllDigits(password) == 0)
        {
            printf("  [!] Password must contain only digits and cannot be empty. Try again.\n\n");
            continue;
        }

        getString("  Confirm Password: ", sizeof(confirmPass), confirmPass);

        if (strcmp(password, confirmPass) != 0)
        {
            printf("  [!] Passwords do not match. Try again.\n\n");
            continue;
        }

        break;
    }

    /* ---- Step 3: Profile information ---- */
    printf("\n");
    printf("  Step 2 of 3: Personal Information\n");
    printf("----------------------------------------------------------------\n");
    printf("\n");

    while (1)
    {
        getString("  \n\nFull Name: ", sizeof(profile.name), profile.name);
        char ch = getCharacter("  [?] Is this correct? (Y/N): ");

        if (ch == 'Y' || ch == 'y')
            break;

        printf("  [!] Please enter your full name again.\n\n");
    }

    while (1)
    {
        getString("  \n\nDepartment (e.g. Computer Science & Engineering): ",
                  sizeof(profile.department), profile.department);
        char ch = getCharacter("  [?] Is this correct? (Y/N): ");

        if (ch == 'Y' || ch == 'y')
            break;

        printf("  [!] Please enter your department again.\n\n");
    }

    while (1)
    {
        getString("  \n\nYear (e.g. 1st Year): ", sizeof(profile.year), profile.year);
        char ch = getCharacter("  [?] Is this correct? (Y/N): ");

        if (ch == 'Y' || ch == 'y')
            break;

        printf("  [!] Please enter your year again.\n\n");
    }

    while (1)
    {
        getString("  \n\nTerm (e.g. 1st Term): ", sizeof(profile.term), profile.term);
        char ch = getCharacter("  [?] Is this correct? (Y/N): ");

        if (ch == 'Y' || ch == 'y')
            break;

        printf("  [!] Please enter your term again.\n\n");
    }

    while (1)
    {
        getString("  \n\nPhone Number (e.g. 01XXXXXXXXX): ",
                  sizeof(profile.phone), profile.phone);
        char ch = getCharacter("  [?] Is this correct? (Y/N): ");

        if (ch == 'Y' || ch == 'y')
            break;

        printf("  [!] Please enter your phone number again.\n\n");
    }

    while (1)
    {
        getString("  \n\nEmail Address: ", sizeof(profile.email), profile.email);
        if (validateEmailFormat(profile.email, STUDENT) == 0)
        {
            char ch = getCharacter("  [?] Is this correct? (Y/N): ");

            if (ch == 'Y' || ch == 'y')
                break;

            printf("  [!] Please enter your email address again.\n\n");
        }
        else
        {
            printf("  [!] Please enter a valid email containing '@'.\n\n");
        }
    }

    printf("  [!] Please fill out the following fields later in your profile after logging in.\n");
    printMenuItems(9, "   Blood Group", "   Father's Name", "   Mother's Name", "   Permanent Address", "   Current Address", "   Academic Advisor", "   Academic Records", "   Hall Details", "   Library Details");
    

    /* ---- Step 4: Write student file ---- */
    printf("\n");
    printf("  Step 3 of 3: Saving account...\n");
    printf("\n");

    /* Build the file header — offsets are derived from struct sizes */
    StudentFileHeader hdr;
    memset(&hdr, 0, sizeof(hdr));
    hdr.studentProfileOffset = (uint32_t)sizeof(StudentFileHeader);
    hdr.academicRecordOffset = (uint32_t)(sizeof(StudentFileHeader) + sizeof(StudentProfile));
    hdr.hallDetailsOffset = (uint32_t)(sizeof(StudentFileHeader) + sizeof(StudentProfile) + sizeof(AcademicRecord));
    hdr.libraryDetailsOffset = (uint32_t)(sizeof(StudentFileHeader) + sizeof(StudentProfile) + sizeof(AcademicRecord) + sizeof(HallDetails));

    /* Zero-initialise remaining sections (academic, hall, library) */
    AcademicRecord academic;
    memset(&academic, 0, sizeof(academic));

    HallDetails hall;
    memset(&hall, 0, sizeof(hall));

    LibraryDetails library;
    memset(&library, 0, sizeof(library));

    /* Create the student file */
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s.student", STUDENTS_DIR, studentId);

    FILE *fp = fopen(filepath, "wb");
    if (fp == NULL)
    {
        printf("  [!] Error: Could not create student file at: %s\n", filepath);
        printf("      Make sure the database/students/ directory exists.\n");
        getCharacter("\n  Press ENTER to return...");
        return;
    }

    int writeOk = (fwrite(&hdr, sizeof(hdr), 1, fp) == 1) &&
                  (fwrite(&profile, sizeof(profile), 1, fp) == 1) &&
                  (fwrite(&academic, sizeof(academic), 1, fp) == 1) &&
                  (fwrite(&hall, sizeof(hall), 1, fp) == 1) &&
                  (fwrite(&library, sizeof(library), 1, fp) == 1);
    if (fclose(fp) != 0)
        writeOk = 0;

    if (!writeOk)
    {
        remove(filepath);
        printf("  [!] Error writing student file. Registration aborted.\n");
        getCharacter("\n  Press ENTER to return...");
        return;
    }

    /* Append credentials record */
    // Create a User struct for the new student
    User user;
    memset(&user, 0, sizeof(user));
    strncpy(user.id, studentId, sizeof(user.id) - 1);
    strncpy(user.pass, password, sizeof(user.pass) - 1);
    user.type = STUDENT;

    // Append to the credentials file
    FILE *cf = fopen(CREDENTIALS_PATH, "ab");
    if (cf == NULL)
    {
        printf("  [!] Error: Could not open credentials file.\n");
        printf("      Student file was created but credentials were NOT saved.\n");
        getCharacter("\n  Press ENTER to return...");
        return;
    }

    int credOk = (fwrite(&user, sizeof(user), 1, cf) == 1);
    if (fclose(cf) != 0)
        credOk = 0;

    if (!credOk)
    {
        remove(filepath);
        printf("  [!] Error writing credentials. Please contact an administrator.\n");
        getCharacter("\n  Press ENTER to return...");
        return;
    }

    /* ---- Success ---- */
    printf("================================================================\n");
    printf("              REGISTRATION SUCCESSFUL!                          \n");
    printf("================================================================\n");
    printf("\n");
    printf("  Student ID : %s\n", studentId);
    printf("  Name       : %s\n", profile.name);
    printf("\n");
    printf("  You can now log in through the Login Portal.\n");
    printf("\n");

    getCharacter("  Press ENTER to return to the Registration Portal...");
}
