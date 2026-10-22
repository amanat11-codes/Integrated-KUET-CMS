#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include "teacherProfilePage.h"
#include "updateMarks.h"
#include "utility.h"
#include "updatePersonalInfo.h"

#define TEACHER_DASHBOARD_LAST_CHOICE 4
#define TEACHER_COURSE_NAME_LENGTH 12

void teacherDashboard(const char *teacherId, const char *filepath)
{
    TeacherFileHeader header;
    TeacherProfile record;
    FILE *fp = fopen(filepath, "rb+");
    if (fp == NULL)
    {
        printf("Error opening file: %s\n", filepath);
        return;
    }
    if (fread(&header, sizeof(header), 1, fp) != 1)
    {
        printf("Error reading teacher file header: %s\n", filepath);
        fclose(fp);
        return;
    }

    if (fseek(fp, (long)header.teacherProfileOffset, SEEK_SET) != 0 ||
        fread(&record, sizeof(record), 1, fp) != 1)
    {
        printf("Error reading teacher profile: %s\n", filepath);
        fclose(fp);
        return;
    }

    while (1)
    {
        clearScreen();
        printBoxedText("TEACHER DASHBOARD PANEL");
        printMenuItems(
            TEACHER_DASHBOARD_LAST_CHOICE,
            "Personal Information",
            "Update Profile",
            "Update CT Marks",
            "Update Term Exam Marks");
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
            if (fseek(fp, (long)header.teacherProfileOffset, SEEK_SET) != 0 ||
                fwrite(&updatedProfile, sizeof(updatedProfile), 1, fp) != 1 ||
                fflush(fp) != 0)
            {
                printf("Error writing updated profile to file: %s\n", filepath);
            }
            else
                record = updatedProfile;
            break;
        case 3:
            updateCTMarks(fp, &header);
            break;
        case 4:
            printf("Update Term Exam Marks functionality is not implemented yet.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}