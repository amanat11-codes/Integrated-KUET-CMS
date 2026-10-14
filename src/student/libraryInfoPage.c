#include <stdio.h>
#include "utility.h"
#include "studentDashboard.h"
#include "libraryInfoPage.h"

void showLibraryInfo(LibraryDetails *record, const char *student_id)
{

    printBoxedText("LIBRARY INFORMATION");

    printf("\n\tStudent ID : %s\n", student_id);

    printf("Title\t\t\tReturn Date\n");
    for (int i = 0; i < 3; i++)
    {
        char dateString[11];
        showDate(record->books[i].returnDate, dateString);
        printf("%s   %s\n", record->books[i].bookTitle, dateString);
    }
    printf("\n\t================================\n");
}

void libraryInfoPage(const char *student_id, const char *filepath)
{
    clearScreen();

    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL)
    {
        printf("Error opening file: %s\n", filepath);
        getCharacter("Press ENTER to return to the student dashboard...");
        return;
    }

    LibraryDetails record;
    StudentFileHeader header;

    fread(&header, sizeof(StudentFileHeader), 1, fp);
    fseek(fp, header.libraryDetailsOffset, SEEK_SET);

    if (fread(&record, sizeof(LibraryDetails), 1, fp) != 1)
    {
        printf("Error reading file: %s\n", filepath);
        fclose(fp);
        getCharacter("Press ENTER to return to the student dashboard...");
        return;
    }
    fclose(fp);

    showLibraryInfo(&record, student_id);
    getCharacter("Press ENTER to return to the student dashboard...");
}