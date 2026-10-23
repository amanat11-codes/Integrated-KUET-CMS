#include <stdio.h>
#include "registrationPortal.h"
#include "teacherRegistrationPage.h"
#include "studentRegistrationPage.h"
#include "adminRegistrationPage.h"
#include "utility.h"

#define REGISTRATION_PORTAL_LAST_CHOICE 3

void registrationPortal(void)
{
    int choice;

    while (1)
    {
        clearScreen();

        printf("\n");
        printf("================================================================\n");
        printf("                                                                \n");
        printf("                  INTEGRATED KUET CMS                          \n");
        printf("                  REGISTRATION PORTAL                          \n");
        printf("                                                                \n");
        printf("================================================================\n");

        printf("\n");
        printf("       Create a new account to access the KUET CMS.\n");
        printf("       Please select the type of account to register.\n");
        printf("\n");

        printf("----------------------------------------------------------------\n");
        printf("                    SELECT ACCOUNT TYPE                         \n");
        printf("----------------------------------------------------------------\n");

        printf("\n");

        printMenuItems(
            REGISTRATION_PORTAL_LAST_CHOICE,
            "Register as Teacher",
            "Register as Student",
            "Register as Admin"
        );

        printf("\n");
        printf("----------------------------------------------------------------\n");
        printf("  0. Back to Main Menu                                          \n");
        printf("----------------------------------------------------------------\n");

        printf("\n");

        choice = getInt("[?]   Enter your choice: ");

        while (choice < 0 || choice > REGISTRATION_PORTAL_LAST_CHOICE)
        {
            printf("\n");
            printf("  [!] Invalid option. Please choose from 0 to %d.\n",
                   REGISTRATION_PORTAL_LAST_CHOICE);

            choice = getInt("[?]   Enter your choice: ");

            if (choice == 0)
                return;
        }

        if (choice == 0)
            return;

        switch (choice)
        {
        case 1:
            teacherRegistrationPage();
            break;

        case 2:
            studentRegistrationPage();
            break;

        case 3:
            adminRegistrationPage();
            break;

        default:
            return;
        }
    }
}
