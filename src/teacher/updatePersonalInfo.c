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
    char newName[NAME_MAX_LENGTH];
    while (1)
    {
        getString("Enter new name: ", sizeof(newName), newName);
        printf("New name: %s\n", newName);
        char response = getCharacter("[?] Save this value? (Y/N): ");
        if (response == 'Y' || response == 'y')
        {
            strcpy(record->name, newName);
            return;
        }
    }
}

void updateDesignation(TeacherProfile *record)
{
    char newDesignation[DESIGNATION_MAX_LENGTH];
    while (1)
    {
        getString("Enter new designation: ", sizeof(newDesignation), newDesignation);
        printf("New designation: %s\n", newDesignation);
        char response = getCharacter("[?] Save this value? (Y/N): ");
        if (response == 'Y' || response == 'y')
        {
            strcpy(record->designation, newDesignation);
            return;
        }
    }
}

void updateDepartment(TeacherProfile *record)
{
    char newDepartment[DEPARTMENT_MAX_LENGTH];
    while (1)
    {
        getString("Enter new department: ", sizeof(newDepartment), newDepartment);
        printf("New department: %s\n", newDepartment);
        char response = getCharacter("[?] Save this value? (Y/N): ");
        if (response == 'Y' || response == 'y')
        {
            strcpy(record->department, newDepartment);
            return;
        }
    }
}

void updatePhone(TeacherProfile *record)
{
    char newPhone[PHONE_MAX_LENGTH];
    while (1)
    {
        getString("Enter new phone number: ", sizeof(newPhone), newPhone);
        printf("New phone number: %s\n", newPhone);
        char response = getCharacter("[?] Save this value? (Y/N): ");
        if (response == 'Y' || response == 'y')
        {
            strcpy(record->phone, newPhone);
            return;
        }
    }
}
void updateEmail(TeacherProfile *record)
{
    char newEmail[EMAIL_MAX_LENGTH];
    while (1)
    {
        getString("Enter new email: ", EMAIL_MAX_LENGTH, newEmail);
        if (validateEmailFormat(newEmail, TEACHER) == 0)
        {
            printf("New email: %s\n", newEmail);
            char response = getCharacter("[?] Save this value? (Y/N): ");
            if (response == 'Y' || response == 'y')
                break;
        }
    }
    strcpy(record->email, newEmail);
    printf("Updated email: %s\n", record->email);
}

void updateResearchInterest(TeacherProfile *record)
{
    char newResearchInterest[RESEARCH_INTEREST_MAX_LENGTH];
    while (1)
    {
        getString("Enter new research interest: ", sizeof(newResearchInterest), newResearchInterest);
        printf("New research interest: %s\n", newResearchInterest);
        char response = getCharacter("[?] Save this value? (Y/N): ");
        if (response == 'Y' || response == 'y')
        {
            strcpy(record->researchSpecialization, newResearchInterest);
            return;
        }
    }
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