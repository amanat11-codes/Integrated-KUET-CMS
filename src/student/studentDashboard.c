#include <stdio.h>
#include <stdlib.h>
#include "studentDashboard.h"
#include "studentProfilePage.h"
#include "academicInfoPage.h"
#include "hallDetailsPage.h"
#include "libraryInfoPage.h"
#include "updateStudentProfile.h"
#include "utility.h"

#define STUDENT_DASHBOARD_LAST_CHOICE 5

void studentDashboard(const char *student_id, const char *filepath)
{
    while (1)
    {
        clearScreen();

        printBoxedText("STUDENT DASHBOARD PANEL");
        printMenuItems(STUDENT_DASHBOARD_LAST_CHOICE, "Student Profile", "Update Profile", "Academic Information", "Hall Details", "Library Information");
        printf("0. Quit\n");


        int choice;
        while (1)
        {
            choice = getInt("[?] Enter your choice: ");
            if (choice < 0 || choice > STUDENT_DASHBOARD_LAST_CHOICE)
                continue;

            if (choice == 0)
                return;

            break;
        }

        while (getchar() != '\n'); // Clear the input buffer
        switch (choice)
        {
        case 1:
            studentProfilePage(student_id, filepath);
            break;
        case 2:
            updateStudentProfile(student_id, filepath);
            break;
        case 3:
            academicInfoPage(student_id, filepath);
            break;
        case 4:
            hallDetailsPage(student_id, filepath);
            break;
        case 5:
            libraryInfoPage(student_id, filepath);
            break;
        default:
            getCharacter("[?] Press ENTER to go back...\n");
            return;
        }
    }
}
