
#include <stdio.h>
#include <stdlib.h>
#include "mainMenu.h"
#include "studentLoginPage.h"
#include "teacherLoginPage.h"
#include "adminLoginPage.h"
#include "noticesPage.h"
#include "utility.h"
#include "loginPortal.h"

#define CHOICE_LAST 3

void mainMenu()
{
    int choice;
    while (1)
    {
        clearScreen();
        printBoxedText("INTEGRATED KUET CMS");
        printf("Welcome to Integrated KUET Campus Management System!\n\n");
        // printf("Today is %s\n", __DATE__);
        printUnderlinedText("Main Menu");
        printMenuItems(CHOICE_LAST, "Login Portal", "Registration Portal", "Notice Board");
        printf("0. Quit\n");

        choice = getInt("> ");

        while (choice < 0 || choice > CHOICE_LAST)
        {
            printf("Please input a valid option...\n");
            choice = getInt("> ");

            if (choice == 0)
            {
                printf("Exiting...\n");
                exit(0);
            }
        }

        if (choice == 0)
        {
            printf("Exiting...\n");
            exit(0);
        }

        switch (choice)
        {
        case 1:
            loginPortal();
            break;
        case 2:
            // registrationPortal();
            break;
        case 3:
            // noticeBoard();
            break;
        default:
            printf("Exiting...\n");
            exit(0);
        }
    }
}
