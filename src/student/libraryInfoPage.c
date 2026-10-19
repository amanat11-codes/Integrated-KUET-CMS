#include <stdio.h>
#include "utility.h"
#include "studentDashboard.h"
#include "libraryInfoPage.h"

void showLibraryInfo(LibraryDetails *record, const char *student_id)
{
    /* Page heading */
    printf("\n\n");
    printBoxedText("LIBRARY INFORMATION");

    printf("\n");
    printf("       INTEGRATED KUET CAMPUS MANAGEMENT SYSTEM\n");
    printf("       ========================================\n\n");

    /* Student information */
    printf("       +------------------------------------------+\n");
    printf("       |              STUDENT DETAILS             |\n");
    printf("       +------------------------------------------+\n");
    printf("       | Student ID : %-27s|\n", student_id);
    printf("       +------------------------------------------+\n\n");

    /* Issued books heading */
    printf("       +------------------------------------------+\n");
    printf("       |               ISSUED BOOKS               |\n");
    printf("       +------------------------------------------+\n\n");

    /* Display the existing three book records */
    for (int i = 0; i < 3; i++)
    {
        char *dateString;

        dateString = showDate(record->books[i].returnDate);

        printf("       +------------------------------------------+\n");
        printf("       | BOOK %-2d                                   |\n", i + 1);
        printf("       |                                          |\n");
        printf("       | Title      : %s\n", record->books[i].bookTitle);
        printf("       | Return Date: %s\n", dateString);
        printf("       +------------------------------------------+\n\n");
    }

    /* Page footer */
    printf("       +------------------------------------------+\n");
    printf("       |              END OF RECORD               |\n");
    printf("       +------------------------------------------+\n");
}

void libraryInfoPage(const char *student_id, const char *filepath)
{
    clearScreen();

    FILE *fp = fopen(filepath, "rb");

    if (fp == NULL)
    {
        printf("\n");
        printBoxedText("LIBRARY INFORMATION");

        printf("\n       Unable to open the library record.\n");
        printf("       File: %s\n\n", filepath);

        getCharacter("Press ENTER to return to the student dashboard...");
        return;
    }

    LibraryDetails record;
    StudentFileHeader header;

    fread(&header, sizeof(StudentFileHeader), 1, fp);

    fseek(fp, header.libraryDetailsOffset, SEEK_SET);

    if (fread(&record, sizeof(LibraryDetails), 1, fp) != 1)
    {
        printf("\n");
        printBoxedText("LIBRARY INFORMATION");

        printf("\n       Unable to read the library record.\n");
        printf("       Please check the student data file.\n\n");

        fclose(fp);

        getCharacter("Press ENTER to return to the student dashboard...");
        return;
    }

    fclose(fp);

    showLibraryInfo(&record, student_id);

    printf("\n");

    getCharacter("Press ENTER to return to the student dashboard...");
}
