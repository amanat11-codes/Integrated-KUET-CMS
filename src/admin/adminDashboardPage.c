#include <stdio.h>
#include <stdlib.h>
#include "addNoticePage.h"
#include "notifications.h"
#include "adminDashboardPage.h"
#include "removeNoticePage.h"
#include "utility.h"

#define LAST_CHOICE 9

void adminDashboard()
{
    while (1)
    {
        clearScreen();
        printBoxedText("ADMIN DASHBOARD PANEL");
        printMenuItems(LAST_CHOICE,
                       "Add notice",
                       "Remove notice",
                       "View notices",
                       "Add Teacher account",
                       "Update Teacher account",
                       "Remove Teacher account",
                       "Add Student account",
                       "Update Student account",
                       "Remove Student account");
        printf("0. Quit\n");

        int choice;
        while ((choice = getInt("> ")) < 1 || choice > LAST_CHOICE)
        {
            printf("Invalid choice. Please try again.\n");
        }

        switch (choice)
        {
        case 1:
            addNotice();
            break;
        case 2:
            removeNoticePage();
            break;
        case 3:
            noticesPage();
            break;
        case 4:
            // addTeacherAccount();
            break;
        case 5:
            // updateTeacherAccount();
            break;
        case 6:
            // removeTeacherAccount();
            break;
        case 7:
            // addStudentAccount();
            break;
        case 8:
            // updateStudentAccount();
            break;
        case 9:
            // removeStudentAccount();
            break;
        default:
            getCharacter("Press ENTER to go back...\n");
            return;
        }
    }
}