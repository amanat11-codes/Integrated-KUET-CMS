#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "teacherRegistrationPage.h"
#include "teacherDashboard.h"
#include "utility.h"

/* ---- Field size limits (max chars, excluding NUL) ---- */
#define ID_MAX_LENGTH 8
#define PASS_MAX_LENGTH 8
#define NAME_MAX_LENGTH 79
#define DESIGNATION_MAX_LENGTH 19
#define DEPARTMENT_MAX_LENGTH 49
#define PHONE_MAX_LENGTH 15
#define EMAIL_MAX_LENGTH 79
#define RESEARCH_MAX_LENGTH 159

/* ---- Paths ---- */
#define CREDENTIALS_PATH "database/credentials.dat"
#define TEACHERS_DIR "database/teachers/"

/* ------------------------------------------------------------------
 * teacherRegistrationPage
 * Collects teacher ID, password, and full profile; writes a record
 * to credentials.dat and creates database/teachers/ID.teacher.
 * ------------------------------------------------------------------ */
void teacherRegistrationPage(void)
{
    char teacherId[ID_MAX_LENGTH + 1];
    char password[PASS_MAX_LENGTH + 1];
    char confirmPass[PASS_MAX_LENGTH + 1];

    /* ---- Profile fields ---- */
    char name[NAME_MAX_LENGTH + 1];
    char designation[DESIGNATION_MAX_LENGTH + 1];
    char department[DEPARTMENT_MAX_LENGTH + 1];
    char phone[PHONE_MAX_LENGTH + 1];
    char email[EMAIL_MAX_LENGTH + 1];

    clearScreen();

    printf("\n");
    printf("================================================================\n");
    printf("                   TEACHER REGISTRATION                         \n");
    printf("================================================================\n");
    printf("\n");

    /* ---- Step 1: Teacher ID ---- */
    printf("  Step 1 of 3: Account Credentials\n");
    printf("----------------------------------------------------------------\n");
    printf("\n");
    printf("  Teacher ID must be %d characters.\n",
           ID_MAX_LENGTH);
    printf("\n");

    while (1)
    {
        getString("[?]   Enter Teacher ID (first 8 digits are taken): ", sizeof(teacherId), teacherId);

        if (teacherId[0] == '\0' || isAllDigits(teacherId) == 0)
        {
            printf("  [!] Teacher ID must contain only digits and cannot be empty. Try again.\n\n");
            continue;
        }

        if (isIdAlreadyRegistered(teacherId))
        {
            printf("  [!] This ID is already registered. Please use a different ID.\n\n");
            continue;
        }

        printf("Teacher ID: %s\n", teacherId);
        char ch = getCharacter("  [?] Are you sure you want to use this ID? (Y/N): ");

        if (ch == 'Y' || ch == 'y')
            break;
        else
        {
            printf("  [!] Please enter a different Teacher ID.\n\n");
            continue;
        }
    }

    /* ---- Step 2: Password (confirmed) ---- */
    printf("\n");
    printf("  Password must be %d characters.\n", PASS_MAX_LENGTH);
    printf("\n");

    while (1)
    {
        getString("[?]   Enter Password (first 8 characters are taken): ", sizeof(password), password);

        if (password[0] == '\0' || isAllDigits(password) == 0)
        {
            printf("  [!] Password must contain only digits and cannot be empty. Try again.\n\n");
            continue;
        }

        getString("[?]   Confirm Password: ", sizeof(confirmPass), confirmPass);

        if (strcmp(password, confirmPass) != 0)
        {
            printf("  [!] Passwords do not match. Try again.\n\n");
            continue;
        }

        break;
    }

    /* ---- Step 3: Profile information ---- */
    printf("\n");
    printf("  Step 2 of 3: Personal & Professional Information\n");
    printf("----------------------------------------------------------------\n");
    printf("\n");

    while (1)
    {
        getString("[?]   \n\nFull Name: ", sizeof(name), name);
        char ch = getCharacter("  [?] Is this correct? (Y/N): ");
        if (ch == 'Y' || ch == 'y')
            break;
        else
            printf("  [!] Please enter your full name again.\n\n");
    }

    while (1)
    {
        getString("[?]   \n\nDesignation (e.g. Professor, Lecturer): ",
                  sizeof(designation), designation);
        char ch = getCharacter("  [?] Is this correct? (Y/N): ");
        if (ch == 'Y' || ch == 'y')
            break;
        else
            printf("  [!] Please enter your designation again.\n\n");
    }

    while (1)
    {
        getString("[?]   \n\nDepartment (e.g. Computer Science & Engineering): ",
                  sizeof(department), department);
        char ch = getCharacter("  [?] Is this correct? (Y/N): ");
        if (ch == 'Y' || ch == 'y')
            break;
        else
            printf("  [!] Please enter your department again.\n\n");
    }

    while (1)
    {
        getString("[?]   \n\nPhone Number (e.g. 01XXXXXXXXX): ",
                  sizeof(phone), phone);
        char ch = getCharacter("  [?] Is this correct? (Y/N): ");
        if (ch == 'Y' || ch == 'y')
            break;
        else
            printf("  [!] Please enter your phone number again.\n\n");
    }

    while (1)
    {
        getString("[?]   \n\nEmail Address: ", sizeof(email), email);
        if (validateEmailFormat(email, TEACHER) == 0)
        {
            char ch = getCharacter("  [?] Is this correct? (Y/N): ");
            if (ch == 'Y' || ch == 'y')
                break;
            else
            {
                printf("  [!] Please enter your email address again.\n\n");
                continue;
            }
        }
        printf("  [!] Please enter a valid email containing '@'.\n\n");
    }

    printf("Please fill out the following fields later in your profile after logging in.\n");
    printMenuItems(4, "Research Specialization", "Course 1", "Course 2", "Course 3");

    /* ---- Step 4: Write teacher file ---- */
    printf("\n");
    printf("  Step 3 of 3: Saving account...\n");
    printf("\n");

    /* Build the file header */
    TeacherFileHeader hdr;
    memset(&hdr, 0, sizeof(hdr));
    hdr.teacherProfileOffset = (uint32_t)sizeof(TeacherFileHeader);
    hdr.taughtCoursesOffset = (uint32_t)(sizeof(TeacherFileHeader) + sizeof(TeacherProfile));
    hdr.taughtCourseCount = 0;

    /* Build the profile */
    TeacherProfile profile;
    memset(&profile, 0, sizeof(profile));
    strncpy(profile.name, name, sizeof(profile.name) - 1);
    strncpy(profile.teacherId, teacherId, sizeof(profile.teacherId) - 1);
    strncpy(profile.designation, designation, sizeof(profile.designation) - 1);
    strncpy(profile.department, department, sizeof(profile.department) - 1);
    strncpy(profile.phone, phone, sizeof(profile.phone) - 1);
    strncpy(profile.email, email, sizeof(profile.email) - 1);

    TaughtCourse courses[3];
    memset(courses, 0, sizeof(courses));

    /* Create the teacher file */
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s.teacher", TEACHERS_DIR, teacherId);

    FILE *fp = fopen(filepath, "wb");
    if (fp == NULL)
    {
        printf("  [!] Error: Could not create teacher file at: %s\n", filepath);
        printf("      Make sure the database/teachers/ directory exists.\n");
        getCharacter("[?] \n  Press ENTER to return...");
        return;
    }

    int writeOk = (fwrite(&hdr, sizeof(hdr), 1, fp) == 1) &&
                  (fwrite(&profile, sizeof(profile), 1, fp) == 1) &&
                  (fwrite(courses, sizeof(courses), 1, fp) == 1);
    if (fclose(fp) != 0)
        writeOk = 0;

    if (!writeOk)
    {
        remove(filepath);
        printf("  [!] Error writing teacher file. Registration aborted.\n");
        getCharacter("[?] \n  Press ENTER to return...");
        return;
    }

    /* Append credentials record */
    // Create a User struct for the new teacher
    User user;
    memset(&user, 0, sizeof(user));
    strncpy(user.id, teacherId, sizeof(user.id) - 1);
    strncpy(user.pass, password, sizeof(user.pass) - 1);
    user.type = TEACHER;

    // Append to the credentials file
    FILE *cf = fopen(CREDENTIALS_PATH, "ab");
    if (cf == NULL)
    {
        printf("  [!] Error: Could not open credentials file.\n");
        printf("      Teacher file was not retained because credentials were NOT saved.\n");
        getCharacter("[?] \n  Press ENTER to return...");
        return;
    }

    int credOk = (fwrite(&user, sizeof(user), 1, cf) == 1);
    if (fclose(cf) != 0)
        credOk = 0;

    if (!credOk)
    {
        remove(filepath);
        printf("  [!] Error writing credentials. Please contact an administrator.\n");
        getCharacter("[?] \n  Press ENTER to return...");
        return;
    }

    /* ---- Success ---- */
    printf("================================================================\n");
    printf("              REGISTRATION SUCCESSFUL!                          \n");
    printf("================================================================\n");
    printf("\n");
    printf("  Teacher ID : %s\n", teacherId);
    printf("  Name       : %s\n", name);
    printf("\n");
    printf("  You can now log in through the Login Portal.\n");
    printf("\n");

    getCharacter("[?]   Press ENTER to return to the Registration Portal...");
}
