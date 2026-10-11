#include <stdio.h>
#include <stdlib.h>
#include "studentDashboard.h"
#include "studentProfilePage.h"
#include "academicInfoPage.h"
#include "hallDetailsPage.h"
#include "libraryInfoPage.h"
#include "teacherProfilePage.h"
#include "utility.h"

#define LAST_CHOICE 6

void studentDashboard(sqlite3 *db, char *student_id)
{
    (void)db;
    (void)student_id;

    while (1)
    {
        clearScreen();
        printBoxedText("STUDENT DASHBOARD PANEL");
        printf("1. Student Profile\n");
        printf("2. Academic Information\n");
        printf("3. Hall Details\n");
        printf("4. Library Information\n");
        printf("5. Teacher Information\n");
        printf("6. Quit\n");

        int choice;
        while ((choice = getInt("> ")) < 1 || choice > LAST_CHOICE)
        {
            printf("Invalid choice. Please try again.\n");
        }

        switch (choice)
        {
            case 1:
                studentProfilePage();
                break;
            case 2:
                academicInfoPage(db, student_id);
                break;
            case 3:
                hallDetailsPage(db, student_id);
                break;
            case 4:
                libraryInfoPage(db, student_id);
                break;
            case 5:
                teacherProfilePage();
                break;
            case 6:
                printf("Exiting...\n");
                sqlite3_close(db);
                exit(0);
        }
    }
}
