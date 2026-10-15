#include <stdio.h>
#include <stdlib.h>
#include "studentDashboard.h"
#include "studentProfilePage.h"
#include "academicInfoPage.h"
#include "hallDetailsPage.h"
#include "libraryInfoPage.h"
#include "teacherProfilePage.h"
#include "utility.h"

#define STUDENT_DASHBOARD_LAST_CHOICE 5





void studentDashboard(const char *student_id, const char *filepath)
{
    while (1)
    {
        clearScreen();
        printBoxedText("STUDENT DASHBOARD PANEL");
        printMenuItems(STUDENT_DASHBOARD_LAST_CHOICE, "Student Profile", "Academic Information", "Hall Details", "Library Information", "Teacher Information");
        printf("0. Quit\n");

        int choice = getInt("> ");

        while (choice < 0 || choice > STUDENT_DASHBOARD_LAST_CHOICE)
        {
            printf("Please input a valid option...\n");
            choice = getInt("> ");

            if (choice == 0)
                return;
        }

        if (choice == 0)
            return;

        switch (choice)
        {
            case 1:
                studentProfilePage(student_id, filepath); // prepare db
                break;
            case 2:
                academicInfoPage(student_id, filepath);
                break;
            case 3:
                hallDetailsPage(student_id, filepath);
                break;
            case 4:
                libraryInfoPage(student_id, filepath); // prepare db
                break;
            case 5:
                //teacherProfilePage();
                break;
            default:
                getCharacter("Press ENTER to go back...\n");
                return;
        }
    }
}
