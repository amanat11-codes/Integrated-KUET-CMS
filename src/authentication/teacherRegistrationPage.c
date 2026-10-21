#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "teacherRegistrationPage.h"
#include "teacherDashboard.h"
#include "utility.h"

/* ---- Field size limits (max chars, excluding NUL) ---- */
#define ID_MAX_LENGTH               8
#define PASS_MAX_LENGTH             8
#define NAME_MAX_LENGTH             79
#define DESIGNATION_MAX_LENGTH      19
#define DEPARTMENT_MAX_LENGTH       49
#define PHONE_MAX_LENGTH            15
#define EMAIL_MAX_LENGTH            79
#define RESEARCH_MAX_LENGTH         159

/* ---- Paths ---- */
#define CREDENTIALS_PATH  "database/credentials.dat"
#define TEACHERS_DIR      "database/teachers/"

/* ------------------------------------------------------------------
 * isIdAlreadyRegistered
 * Opens credentials.dat and scans every User record for a matching
 * id string (regardless of user type).  Returns 1 if found, 0 if not.
 * ------------------------------------------------------------------ */
static int isIdAlreadyRegistered(const char *id)
{
    FILE *cf = fopen(CREDENTIALS_PATH, "rb");
    if (cf == NULL)
        return 0; /* file absent: ID cannot be taken */

    User u;
    while (fread(&u, sizeof(User), 1, cf) == 1)
    {
        if (strcmp(u.id, id) == 0)
        {
            fclose(cf);
            return 1;
        }
    }
    fclose(cf);
    return 0;
}

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
    char research[RESEARCH_MAX_LENGTH + 1];

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
    printf("  Teacher ID must be exactly %d characters (digits only).\n",
           ID_MAX_LENGTH);
    printf("\n");

    while (1)
    {
        getString("  Enter Teacher ID (8 digits): ", sizeof(teacherId), teacherId);

        if ((int)strlen(teacherId) != ID_MAX_LENGTH)
        {
            printf("  [!] Teacher ID must be exactly %d characters. Try again.\n\n",
                   ID_MAX_LENGTH);
            continue;
        }

        if (isIdAlreadyRegistered(teacherId))
        {
            printf("  [!] This ID is already registered. Please use a different ID.\n\n");
            continue;
        }

        break;
    }

    /* ---- Step 2: Password (confirmed) ---- */
    printf("\n");
    printf("  Password must be exactly %d characters.\n", PASS_MAX_LENGTH);
    printf("\n");

    while (1)
    {
        getString("  Enter Password (8 chars): ", sizeof(password), password);

        if ((int)strlen(password) != PASS_MAX_LENGTH)
        {
            printf("  [!] Password must be exactly %d characters. Try again.\n\n",
                   PASS_MAX_LENGTH);
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
    printf("  Step 2 of 3: Personal & Professional Information\n");
    printf("----------------------------------------------------------------\n");
    printf("\n");

    getString("  Full Name: ", sizeof(name), name);

    getString("  Designation (e.g. Professor, Lecturer): ",
              sizeof(designation), designation);

    getString("  Department (e.g. Computer Science & Engineering): ",
              sizeof(department), department);

    getString("  Phone Number (e.g. 01XXXXXXXXX): ",
              sizeof(phone), phone);

    while (1)
    {
        getString("  Email Address: ", sizeof(email), email);
        if (validateEmailFormat(email, TEACHER) == 0)
            break;
        printf("  [!] Please enter a valid email containing '@'.\n\n");
    }

    printf("  Research Specialization (optional, press ENTER to skip): ");
    getString("", sizeof(research), research);

    /* ---- Step 4: Write teacher file ---- */
    printf("\n");
    printf("  Step 3 of 3: Saving account...\n");
    printf("\n");

    /* Build the file header */
    TeacherFileHeader hdr;
    memset(&hdr, 0, sizeof(hdr));
    hdr.teacherProfileOffset = (uint32_t)sizeof(TeacherFileHeader);
    hdr.taughtCoursesOffset  = (uint32_t)(sizeof(TeacherFileHeader)
                                          + sizeof(TeacherProfile));
    hdr.taughtCourseCount    = 0;

    /* Build the profile */
    TeacherProfile profile;
    memset(&profile, 0, sizeof(profile));
    strncpy(profile.name,                  name,        sizeof(profile.name)                  - 1);
    strncpy(profile.teacherId,             teacherId,   sizeof(profile.teacherId)              - 1);
    strncpy(profile.designation,           designation, sizeof(profile.designation)            - 1);
    strncpy(profile.department,            department,  sizeof(profile.department)             - 1);
    strncpy(profile.phone,                 phone,       sizeof(profile.phone)                  - 1);
    strncpy(profile.email,                 email,       sizeof(profile.email)                  - 1);
    strncpy(profile.researchSpecialization, research,   sizeof(profile.researchSpecialization) - 1);

    /* Create the teacher file */
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s.teacher", TEACHERS_DIR, teacherId);

    FILE *fp = fopen(filepath, "wb");
    if (fp == NULL)
    {
        printf("  [!] Error: Could not create teacher file at: %s\n", filepath);
        printf("      Make sure the database/teachers/ directory exists.\n");
        getCharacter("\n  Press ENTER to return...");
        return;
    }

    int writeOk = (fwrite(&hdr,     sizeof(hdr),     1, fp) == 1) &&
                  (fwrite(&profile, sizeof(profile), 1, fp) == 1);
    fclose(fp);

    if (!writeOk)
    {
        printf("  [!] Error writing teacher file. Registration aborted.\n");
        getCharacter("\n  Press ENTER to return...");
        return;
    }

    /* Append credentials record */
    User user;
    memset(&user, 0, sizeof(user));
    strncpy(user.id,   teacherId, sizeof(user.id)   - 1);
    strncpy(user.pass, password,  sizeof(user.pass)  - 1);
    user.type = TEACHER;

    FILE *cf = fopen(CREDENTIALS_PATH, "ab");
    if (cf == NULL)
    {
        printf("  [!] Error: Could not open credentials file.\n");
        printf("      Teacher file was created but credentials were NOT saved.\n");
        getCharacter("\n  Press ENTER to return...");
        return;
    }

    int credOk = (fwrite(&user, sizeof(User), 1, cf) == 1);
    fclose(cf);

    if (!credOk)
    {
        printf("  [!] Error writing credentials. Please contact an administrator.\n");
        getCharacter("\n  Press ENTER to return...");
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

    getCharacter("  Press ENTER to return to the Registration Portal...");
}
