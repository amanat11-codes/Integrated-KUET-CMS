#include <stdio.h>
#include "studentDashboard.h"
#include "ctMarksPage.h"

static void showCTMarks(const AcademicRecord *record, const char *student_id)
{
    printf("\n");
    printBoxedText("CT MARKS");
    printf("Student ID : %s\n", student_id);
    printf("Name       : %s\n", record->name);
    printf("Department : %s (%s)\n", record->departmentName, record->departmentShortName);
    printf("Session    : %d     Year : %d     Term : %d\n",
           record->session, record->year, record->term);

    printf("---------------------------------------------------------------\n");
    printf("Sl.  Course Code.    Course Title                  CT Marks\n");
    printf("------------------------------------------------------------------\n");

    for (int j = 0; j < 8; j++)
    {
        printf("%-4d %-13s %-35s %.2f\n",
               j + 1,
               record->courses[j].courseShortName,
               record->courses[j].courseTitle,
               record->courses[j].ctMarks);
    }

    printf("===============================================================\n");
}

void ctMarksPage(const char *student_id, const char *filepath)
{
    clearScreen();

    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL)
    {
        printf("[!] Error opening file: %s\n", filepath);
        getCharacter("[?] Press ENTER to return to the student dashboard...");
        return;
    }

    AcademicRecord record;
    StudentFileHeader header;
    if (fread(&header, sizeof(header), 1, fp) != 1 ||
        fseek(fp, (long)header.academicRecordOffset, SEEK_SET) != 0 ||
        fread(&record, sizeof(record), 1, fp) != 1)
    {
        printf("[!] Error reading academic record: %s\n", filepath);
        fclose(fp);
        getCharacter("[?] Press ENTER to return to the student dashboard...");
        return;
    }
    fclose(fp);

    showCTMarks(&record, student_id);
    getCharacter("[?] Press ENTER to return to the student dashboard...");
}
