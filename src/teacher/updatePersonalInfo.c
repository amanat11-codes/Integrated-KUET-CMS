#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "teacherDashboard.h"
#include "teacherProfilePage.h"
#include "updatePersonalInfo.h"

#define NAME_MAX_LENGTH 80
#define DESIGNATION_MAX_LENGTH 20
#define DEPARTMENT_MAX_LENGTH 50
#define PHONE_MAX_LENGTH 16
#define EMAIL_MAX_LENGTH 80
#define RESEARCH_INTEREST_MAX_LENGTH 160

static int confirmValue(const char *field, const char *value)
{
    printf("%s: %s\n", field, value);
    char response = getCharacter("[?] Save this value? (Y/N): ");
    return response == 'Y' || response == 'y';
}

static void updateStringField(const char *field, char *destination, size_t size)
{
    char value[RESEARCH_INTEREST_MAX_LENGTH];

    while (1)
    {
        char prompt[192];
        snprintf(prompt, sizeof(prompt), "[?] Enter new %s: ", field);
        getString(prompt, (int)sizeof(value), value);

        if (value[0] == '\0')
        {
            printf("[!] Empty input. Please enter a value.\n");
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

static void updateName(TeacherProfile *record)
{
    updateStringField("name", record->name, sizeof(record->name));
}

static void updateDesignation(TeacherProfile *record)
{
    updateStringField("designation", record->designation, sizeof(record->designation));
}

static void updateDepartment(TeacherProfile *record)
{
    updateStringField("department", record->department, sizeof(record->department));
}

static void updatePhone(TeacherProfile *record)
{
    updateStringField("phone number", record->phone, sizeof(record->phone));
}

static void updateEmail(TeacherProfile *record)
{
    char newEmail[EMAIL_MAX_LENGTH];
    while (1)
    {
        getString("[?] Enter new email: ", EMAIL_MAX_LENGTH, newEmail);
        if (newEmail[0] == '\0')
        {
            printf("[!] Empty input. Please enter a value.\n");
            continue;
        }

        if (validateEmailFormat(newEmail, TEACHER) == 0)
        {
            if (confirmValue("email", newEmail))
            {
                strncpy(record->email, newEmail, sizeof(record->email) - 1);
                record->email[sizeof(record->email) - 1] = '\0';
                return;
            }
        }
        else
            printf("[!] Please enter a valid email containing '@'.\n");
    }
}

static void updateResearchInterest(TeacherProfile *record)
{
    updateStringField("research interest", record->researchSpecialization,
                      sizeof(record->researchSpecialization));
}

TeacherProfile updatePersonalInfo(TeacherProfile *record, const char *teacher_id, const char *filepath)
{
    (void)filepath;
    clearScreen();
    printBoxedText("UPDATE PERSONAL INFORMATION");
    printUnderlinedText("Current Information:\n");

    showTeacherProfile(record, teacher_id);
    printf("\n\n");

    TeacherProfile updatedProfile;
    updatedProfile = *record; // Initialize updatedProfile with current record

    while (1)
    {

        int ch = getInt("[?] Which information would you like to update? (1-Name, 2-Designation, 3-Department, 4-Phone, 5-Email, 6-Research Interest, 0-Exit): ");

        switch (ch)
        {
        case 1:
            updateName(&updatedProfile);
            break;
        case 2:
            updateDesignation(&updatedProfile);
            break;
        case 3:
            updateDepartment(&updatedProfile);
            break;
        case 4:
            updatePhone(&updatedProfile);
            break;
        case 5:
            updateEmail(&updatedProfile);
            break;
        case 6:
            updateResearchInterest(&updatedProfile);
            break;
        case 0:
            printf("Profile update completed.");
            return updatedProfile;
        default:
            printf("[!] Invalid choice. Please try again.\n");
            break;
        }
    }
}