#include <stdio.h>
#include <string.h>
#include "studentDashboard.h"
#include "academicInfoPage.h"

void showAcademicRecord(AcademicRecord *record, const char *student_id)
{
    printf("\n");
    printBoxedText("ACADEMIC INFORMATION");
    printf("Student ID : %s\n", student_id);
    printf("Name       : %s\n", record->name);
    printf("Department : %s (%s)\n", record->departmentName, record->departmentShortName);
    printf("Session    : %d     Year : %d     Term : %d\n",
           record->session, record->year, record->term);

    printf("---------------------------------------------------------------\n");

    printf("Sl.  Course Code.    Course Title                  Credit  GPA  Grade\n");
    printf("------------------------------------------------------------------\n");

    for (int j = 0; j < 5; j++)
    {
        printf("%-4d %-13s %-35s %.2f   %.2f  %s\n",
               j + 1,
               record->courses[j].courseShortName,
               record->courses[j].courseTitle,
               record->courses[j].courseCredit,
               record->courses[j].gradePoint,
               record->courses[j].letterGrade);
    }

    printf("---------------------------------------------------------------\n");

    printf("Credit Taken           : %.2f\n", record->creditTaken);
    printf("Credit Completed       : %.2f\n", record->creditCompleted);
    printf("Term GPA               : %.2f\n", record->termGPA);
    printf("CGPA                   : %.2f\n", record->cgpa);

    printf("===============================================================\n");

    return;
}

void academicInfoPage(const char *student_id, const char *filepath)
{
    clearScreen();

    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL)
    {
        printf("Error opening file: %s\n", filepath);
        getCharacter("Press ENTER to return to the student dashboard...");
        return;
    }

    AcademicRecord record;
    StudentFileHeader header;

    fread(&header, sizeof(StudentFileHeader), 1, fp);
    fseek(fp, header.academicRecordOffset, SEEK_SET);

    if (fread(&record, sizeof(AcademicRecord), 1, fp) != 1)
    {
        printf("Error reading file: %s\n", filepath);
        fclose(fp);
        getCharacter("Press ENTER to return to the student dashboard...");
        return;
    }
    fclose(fp);

    showAcademicRecord(&record, student_id);
    getCharacter("Press ENTER to return to the student dashboard...");

    return;
}