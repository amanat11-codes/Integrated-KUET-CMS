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

void updateName(TeacherProfile *record)
{
    char *newName = malloc(NAME_MAX_LENGTH * sizeof(char));
    getString("Enter new name: ", NAME_MAX_LENGTH, newName);
    strcpy(record->name, newName);
    printf("Updated name: %s\n", record->name);
    free(newName);
}

void updateDesignation(TeacherProfile *record)
{
    char *newDesignation = malloc(DESIGNATION_MAX_LENGTH * sizeof(char));
    getString("Enter new designation: ", DESIGNATION_MAX_LENGTH, newDesignation);
    strcpy(record->designation, newDesignation);
    printf("Updated designation: %s\n", record->designation);
    free(newDesignation);
}

void updateDepartment(TeacherProfile *record)
{
    char *newDepartment = malloc(DEPARTMENT_MAX_LENGTH * sizeof(char));
    getString("Enter new department: ", DEPARTMENT_MAX_LENGTH, newDepartment);
    strcpy(record->department, newDepartment);
    printf("Updated department: %s\n", record->department);
    free(newDepartment);
}

void updatePhone(TeacherProfile *record)
{
    char *newPhone = malloc(PHONE_MAX_LENGTH * sizeof(char));
    getString("Enter new phone number: ", PHONE_MAX_LENGTH, newPhone);
    strcpy(record->phone, newPhone);
    printf("Updated phone number: %s\n", record->phone);
    free(newPhone);
}
void updateEmail(TeacherProfile *record)
{
    char *newEmail = malloc(EMAIL_MAX_LENGTH * sizeof(char));
    while (1)
    {
        getString("Enter new email: ", EMAIL_MAX_LENGTH, newEmail);
        if (validateEmailFormat(newEmail, TEACHER) == 0)
        {
            break; // Valid email format
        }
    }
    strcpy(record->email, newEmail);
    printf("Updated email: %s\n", record->email);
    free(newEmail);
}

void updateResearchInterest(TeacherProfile *record)
{
    char *newResearchInterest = malloc(RESEARCH_INTEREST_MAX_LENGTH * sizeof(char));
    getString("Enter new research interest: ", RESEARCH_INTEREST_MAX_LENGTH, newResearchInterest);
    strcpy(record->researchSpecialization, newResearchInterest);
    printf("Updated research interest: %s\n", record->researchSpecialization);
    free(newResearchInterest);
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

        int ch = getInt("Which information would you like to update? (1-Name, 2-Designation, 3-Department, 4-Phone, 5-Email, 6-Research Interest, 0-Exit): ");

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
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}