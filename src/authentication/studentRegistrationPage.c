#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "studentRegistrationPage.h"
#include "studentDashboard.h"
#include "utility.h"

/* ---- Field size limits (max chars, excluding NUL) ---- */
#define ID_MAX_LENGTH               8
#define PASS_MAX_LENGTH             8
#define NAME_MAX_LENGTH             79
#define DEPARTMENT_MAX_LENGTH       49
#define YEAR_MAX_LENGTH             11
#define TERM_MAX_LENGTH             11
#define PHONE_MAX_LENGTH            15
#define EMAIL_MAX_LENGTH            79
#define BLOOD_GROUP_MAX_LENGTH      3
#define FATHERS_NAME_MAX_LENGTH     79
#define MOTHERS_NAME_MAX_LENGTH     79
#define PERM_ADDRESS_MAX_LENGTH     159
#define CURR_ADDRESS_MAX_LENGTH     159
#define ADVISOR_MAX_LENGTH          79

/* ---- Paths ---- */
#define CREDENTIALS_PATH  "database/credentials.dat"
#define STUDENTS_DIR      "database/students/"

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
    char name[NAME_MAX_LENGTH + 1];
    char department[DEPARTMENT_MAX_LENGTH + 1];
    char year[YEAR_MAX_LENGTH + 1];
    char term[TERM_MAX_LENGTH + 1];
    char phone[PHONE_MAX_LENGTH + 1];
    char email[EMAIL_MAX_LENGTH + 1];
    char bloodGroup[BLOOD_GROUP_MAX_LENGTH + 1];
    char fathersName[FATHERS_NAME_MAX_LENGTH + 1];
    char mothersName[MOTHERS_NAME_MAX_LENGTH + 1];
    char permanentAddress[PERM_ADDRESS_MAX_LENGTH + 1];
    char currentAddress[CURR_ADDRESS_MAX_LENGTH + 1];
    char advisor[ADVISOR_MAX_LENGTH + 1];

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
    printf("  Student ID must be exactly %d characters (digits only).\n",
           ID_MAX_LENGTH);
    printf("\n");

    while (1)
    {
        getString("  Enter Student ID (8 digits): ", sizeof(studentId), studentId);

        if ((int)strlen(studentId) != ID_MAX_LENGTH)
        {
            printf("  [!] Student ID must be exactly %d characters. Try again.\n\n",
                   ID_MAX_LENGTH);
            continue;
        }

        if (isIdAlreadyRegistered(studentId))
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
    printf("  Step 2 of 3: Personal Information\n");
    printf("----------------------------------------------------------------\n");
    printf("\n");

    getString("  Full Name: ", sizeof(name), name);

    getString("  Department (e.g. Computer Science & Engineering): ",
              sizeof(department), department);

    getString("  Year (e.g. 1st Year): ", sizeof(year), year);

    getString("  Term (e.g. 1st Term): ", sizeof(term), term);

    getString("  Phone Number (e.g. 01XXXXXXXXX): ", sizeof(phone), phone);

    while (1)
    {
        getString("  Email Address: ", sizeof(email), email);
        if (validateEmailFormat(email, STUDENT) == 0)
            break;
        printf("  [!] Please enter a valid email containing '@'.\n\n");
    }

    getString("  Blood Group (e.g. A+, O-): ", sizeof(bloodGroup), bloodGroup);

    getString("  Father's Name: ", sizeof(fathersName), fathersName);

    getString("  Mother's Name: ", sizeof(mothersName), mothersName);

    getString("  Permanent Address: ", sizeof(permanentAddress), permanentAddress);

    getString("  Current Address: ", sizeof(currentAddress), currentAddress);

    getString("  Academic Advisor (optional, press ENTER to skip): ",
              sizeof(advisor), advisor);

    /* ---- Step 4: Write student file ---- */
    printf("\n");
    printf("  Step 3 of 3: Saving account...\n");
    printf("\n");

    /* Build the file header — offsets are derived from struct sizes */
    StudentFileHeader hdr;
    memset(&hdr, 0, sizeof(hdr));
    hdr.studentProfileOffset  = (uint32_t)sizeof(StudentFileHeader);
    hdr.academicRecordOffset  = (uint32_t)(sizeof(StudentFileHeader)
                                           + sizeof(StudentProfile));
    hdr.hallDetailsOffset     = (uint32_t)(sizeof(StudentFileHeader)
                                           + sizeof(StudentProfile)
                                           + sizeof(AcademicRecord));
    hdr.libraryDetailsOffset  = (uint32_t)(sizeof(StudentFileHeader)
                                           + sizeof(StudentProfile)
                                           + sizeof(AcademicRecord)
                                           + sizeof(HallDetails));

    /* Build the student profile */
    StudentProfile profile;
    memset(&profile, 0, sizeof(profile));
    strncpy(profile.name,             name,             sizeof(profile.name)             - 1);
    strncpy(profile.department,       department,       sizeof(profile.department)       - 1);
    strncpy(profile.year,             year,             sizeof(profile.year)             - 1);
    strncpy(profile.term,             term,             sizeof(profile.term)             - 1);
    strncpy(profile.phone,            phone,            sizeof(profile.phone)            - 1);
    strncpy(profile.email,            email,            sizeof(profile.email)            - 1);
    strncpy(profile.bloodGroup,       bloodGroup,       sizeof(profile.bloodGroup)       - 1);
    strncpy(profile.fathersName,      fathersName,      sizeof(profile.fathersName)      - 1);
    strncpy(profile.mothersName,      mothersName,      sizeof(profile.mothersName)      - 1);
    strncpy(profile.permanentAddress, permanentAddress, sizeof(profile.permanentAddress) - 1);
    strncpy(profile.currentAddress,   currentAddress,   sizeof(profile.currentAddress)   - 1);
    strncpy(profile.advisor,          advisor,          sizeof(profile.advisor)          - 1);

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

    int writeOk = (fwrite(&hdr,      sizeof(hdr),      1, fp) == 1) &&
                  (fwrite(&profile,  sizeof(profile),  1, fp) == 1) &&
                  (fwrite(&academic, sizeof(academic), 1, fp) == 1) &&
                  (fwrite(&hall,     sizeof(hall),     1, fp) == 1) &&
                  (fwrite(&library,  sizeof(library),  1, fp) == 1);
    fclose(fp);

    if (!writeOk)
    {
        printf("  [!] Error writing student file. Registration aborted.\n");
        getCharacter("\n  Press ENTER to return...");
        return;
    }

    /* Append credentials record */
    User user;
    memset(&user, 0, sizeof(user));
    strncpy(user.id,   studentId, sizeof(user.id)   - 1);
    strncpy(user.pass, password,  sizeof(user.pass)  - 1);
    user.type = STUDENT;

    FILE *cf = fopen(CREDENTIALS_PATH, "ab");
    if (cf == NULL)
    {
        printf("  [!] Error: Could not open credentials file.\n");
        printf("      Student file was created but credentials were NOT saved.\n");
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
    printf("  Student ID : %s\n", studentId);
    printf("  Name       : %s\n", name);
    printf("\n");
    printf("  You can now log in through the Login Portal.\n");
    printf("  Note: Academic, Hall, and Library records will be populated\n");
    printf("        by an administrator.\n");
    printf("\n");

    getCharacter("  Press ENTER to return to the Registration Portal...");
}
