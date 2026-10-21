#include <stdio.h>
#include <stdlib.h>
#include "mainMenu.h"
#include "studentLoginPage.h"
#include "teacherLoginPage.h"
#include "adminLoginPage.h"
#include "noticesPage.h"
#include "utility.h"
#include "loginPortal.h"
#include "registrationPortal.h"

#define CHOICE_LAST 3

void mainMenu()
{
    int choice;

    while (1)
    {
        clearScreen();

        printf("\n");
        printf("================================================================\n");
        printf("                                                                \n");
        printf("                  KHULNA UNIVERSITY OF                          \n");
        printf("              ENGINEERING & TECHNOLOGY                          \n");
        printf("                                                                \n");
        printf("                  INTEGRATED KUET                     \n");
        printf("              CAMPUS MANAGEMENT SYSTEM                          \n");
        printf("                                                                \n");
        printf("================================================================\n");

        printf("\n");
        printf("       Welcome to the KUET Campus Management System!\n");
        printf("       One Campus. One System. One Community.\n");
        printf("\n");

        printf("----------------------------------------------------------------\n");
        printf("                         MAIN MENU                              \n");
        printf("----------------------------------------------------------------\n");

        printf("\n");

        printMenuItems(
            CHOICE_LAST,
            "Login Portal",
            "Registration Portal",
            "Notice Board"
        );

        printf("\n");
        printf("----------------------------------------------------------------\n");
        printf("  0. Quit                                                       \n");
        printf("----------------------------------------------------------------\n");

        printf("\n");
        choice = getInt("  Enter your choice: ");

        while (choice < 0 || choice > CHOICE_LAST)
        {
            printf("\n");
            printf("  [!] Invalid option. Please choose from 0 to %d.\n",
                   CHOICE_LAST);

            choice = getInt("  Enter your choice: ");

            if (choice == 0)
            {
                printf("\n");
                printf("  Thank you for using KUET CMS!\n");
                printf("  Exiting application...\n");
                exit(0);
            }
        }

        if (choice == 0)
        {
            printf("\n");
            printf("  Thank you for using KUET CMS!\n");
            printf("  Exiting application...\n");
            exit(0);
        }

        switch (choice)
        {
        case 1:
            loginPortal();
            break;

        case 2:
            registrationPortal();
            break;

        case 3:
            noticesPage();
            break;

        default:
            printf("Exiting...\n");
            exit(0);
        }
    }
}
