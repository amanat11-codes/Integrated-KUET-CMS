#include <stdio.h>
#include "utility.h"
#include "studentDashboard.h"

void showStudentProfile(StudentProfile *record, const char *student_id)
{
    printf("Name                   %s\n", record->name);
    printf("Student ID             %s\n", student_id);
    printf("Department             %s\n", record->department);
    printf("Year                   %s\t\tTerm:     %s\n", record->year, record->term);
    printf("Phone                  %s\n"
           "Email                  %s\n", record->phone, record->email);
    printf("Blood group            %s\n", record->bloodGroup);
    printf("Father's name          %s\n", record->fathersName);
    printf("Mother's name          %s\n", record->mothersName);
    printf("Permanent address      %s\n", record->permanentAddress);
    printf("Current address        %s\n", record->currentAddress);
    printf("Advisor                %s\n", record->advisor);
    
    
}




void studentProfilePage(const char *student_id, const char *filepath)
{
    clearScreen();
    printBoxedText("STUDENT PROFILE PAGE");

    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL)
    {
        printf("Error opening file: %s\n", filepath);
        getCharacter("Press ENTER to return to the student dashboard...");
        return;
    }

    StudentProfile record;
    StudentFileHeader header;

    fread(&header, sizeof(StudentFileHeader), 1, fp);
    fseek(fp, header.studentProfileOffset, SEEK_SET);

    if (fread(&record, sizeof(StudentProfile), 1, fp) != 1)
    {
        printf("Error reading file: %s\n", filepath);
        fclose(fp);
        getCharacter("Press ENTER to return to the student dashboard...");
        return;
    }
    fclose(fp);

    showStudentProfile(&record, student_id);
    getCharacter("Press ENTER to return to the student dashboard...");

    return;



    // Nayeem
}