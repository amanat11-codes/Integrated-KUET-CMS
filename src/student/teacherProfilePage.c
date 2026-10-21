#include <stdio.h>
#include <stdint.h>
#include "utility.h"
#include "teacherProfilePage.h"


void showTeacherProfile(const TeacherProfile *record,
                               const char *teacherId)
{
    clearScreen();
    printBoxedText("TEACHER PROFILE PAGE");

    printf("Name                   %s\n", record->name);
    printf("Teacher ID             %s\n", teacherId);
    printf("Designation            %s\n", record->designation);
    printf("Department             %s\n", record->department);
    printf("Phone                  %s\n", record->phone);
    printf("Email                  %s\n", record->email);
    printf("Research interest     %s\n", record->researchSpecialization);
}

void teacherProfilePage(const char *teacherId, const char *filepath)
{
    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL)
    {
        clearScreen();
        printBoxedText("TEACHER PROFILE PAGE");
        printf("Error opening file: %s\n", filepath);
        getCharacter("Press ENTER to return to the teacher dashboard...");
        return;
    }

    TeacherFileHeader header;
    if (fread(&header, sizeof(header), 1, fp) != 1 ||
        header.teacherProfileOffset < sizeof(header) ||
        fseek(fp, (long)header.teacherProfileOffset, SEEK_SET) != 0)
    {
        clearScreen();
        printBoxedText("TEACHER PROFILE PAGE");
        printf("Error reading teacher file header: %s\n", filepath);
        fclose(fp);
        getCharacter("Press ENTER to return to the teacher dashboard...");
        return;
    }

    TeacherProfile record;
    if (fread(&record, sizeof(record), 1, fp) != 1)
    {
        clearScreen();
        printBoxedText("TEACHER PROFILE PAGE");
        printf("Error reading file: %s\n", filepath);
        fclose(fp);
        getCharacter("Press ENTER to return to the teacher dashboard...");
        return;
    }

    fclose(fp);
    showTeacherProfile(&record, teacherId);
    getCharacter("Press ENTER to return to the teacher dashboard...");

}