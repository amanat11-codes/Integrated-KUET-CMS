#include <stdio.h>
#include <stdlib.h>
#include "addNoticePage.h"
#include "adminDashboardPage.h"
#include "removeNoticePage.h"
#include "teacherRegistrationPage.h"
#include "studentRegistrationPage.h"
#include "utility.h"

#define LAST_CHOICE 5

void adminDashboard(void)
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
                       "Add Student account");
        printf("0. Quit\n");

        int choice;
        while ((choice = getInt("[?] > ")) < 0 || choice > LAST_CHOICE)
        {
            printf("[!] Invalid choice. Please try again.\n");
        }

        if (choice == 0)
            return;

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
            teacherRegistrationPage();
            break;
        case 5:
            studentRegistrationPage();
            break;
        default:
            getCharacter("[?] Press ENTER to go back...\n");
            return;
        }
    }
}