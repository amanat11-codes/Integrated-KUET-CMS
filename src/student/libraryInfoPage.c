#include <stdio.h>
#include "utility.h"
#include <string.h>
#include <stdlib.h>
#include "studentDashboard.h"
#include "libraryInfoPage.h"

void showLibraryInfo(LibraryDetails *record, const char *student_id)
{
    /* Page heading */
    printf("\n\n");
    printBoxedText("LIBRARY INFORMATION");

    printAppHeader();

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
        printf("       +------------------------------------------+\n");
        printf("       | BOOK %-2d                                  |\n", i + 1);
        printf("       |                                          |\n");
        
        
        if (strlen(record->books[i].bookTitle) == 0)
        {
            printf("       | Title      : N/A\n");
            printf("       | Return Date: N/A\n");
        }
        else
        {
            printf("       | Title      : %-27s|\n", record->books[i].bookTitle);
            printf("       | Return Date: %s\n", showDate(record->books[i].returnDate));    
        }
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
    printf("File path %s\n", filepath);
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
