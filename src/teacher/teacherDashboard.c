#include <stdio.h>
#include "utility.h"
#include "teacherProfilePage.h"
#include "updatePersonalInfo.h"

#define TEACHER_DASHBOARD_LAST_CHOICE 2

void teacherDashboard(const char *teacherId, const char *filepath)
{
    TeacherProfile record;
    FILE *fp = fopen(filepath, "rb+");
    if (fp == NULL)
    {
        printf("Error opening file: %s\n", filepath);
        return;
    }
    if (fread(&record, sizeof(TeacherProfile), 1, fp) != 1)
    {
        printf("Error reading file: %s\n", filepath);
        fclose(fp);
        return;
    }

    while (1)
    {
        clearScreen();
        printf("Got teacher ID: %s\n", teacherId);
        printf("Got filepath: %s\n", filepath);
        printBoxedText("TEACHER DASHBOARD PANEL");
        printMenuItems(
            TEACHER_DASHBOARD_LAST_CHOICE,
            "Personal Information",
            "Update Personal Information");
        printf("0. Quit\n");

        int choice = getInt("> ");

        while (choice < 0 || choice > TEACHER_DASHBOARD_LAST_CHOICE)
        {
            printf("Please input a valid option...\n");
            choice = getInt("> ");

            if (choice == 0)
            {
                fclose(fp);
                return;
            }
        }

        if (choice == 0)
        {
            fclose(fp);
            return;
        }

        switch (choice)
        {
        case 1:
            teacherProfilePage(teacherId, filepath);
            break;
        case 2:
            TeacherProfile updatedProfile = updatePersonalInfo(&record, teacherId, filepath);
            if (fseek(fp, 0, SEEK_SET) != 0 ||
                fwrite(&updatedProfile, sizeof(updatedProfile), 1, fp) != 1 ||
                fflush(fp) != 0)
            {
                printf("Error writing updated profile to file: %s\n", filepath);
            }
            else
            {
                record = updatedProfile;
            }
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}