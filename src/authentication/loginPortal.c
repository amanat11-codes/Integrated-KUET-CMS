#include <stdio.h>
#include "loginPortal.h"
#include "studentLoginPage.h"
#include "teacherLoginPage.h"
#include "adminLoginPage.h"
#include "utility.h"

#define LOGIN_PORTAL_LAST_CHOICE 3

void loginPortal()
{
    int choice;

    while (1)
    {
        clearScreen();

        printf("\n");
        printf("================================================================\n");
        printf("                                                                \n");
        printf("                  INTEGRATED KUET CMS                           \n");
        printf("                     LOGIN PORTAL                               \n");
        printf("                                                                \n");
        printf("================================================================\n");

        printf("\n");
        printf("       Welcome to the KUET CMS Login Portal!\n");
        printf("       Please select your account type to continue.\n");
        printf("\n");

        printf("----------------------------------------------------------------\n");
        printf("                    SELECT ACCOUNT TYPE                         \n");
        printf("----------------------------------------------------------------\n");

        printf("\n");

        printMenuItems(
            LOGIN_PORTAL_LAST_CHOICE,
            "Teacher Login",
            "Student Login",
            "Admin Login"
        );

        printf("\n");
        printf("----------------------------------------------------------------\n");
        printf("  0. Back to Main Menu                                           \n");
        printf("----------------------------------------------------------------\n");

        printf("\n");

        choice = getInt("  Enter your choice: ");

        while (choice < 0 || choice > LOGIN_PORTAL_LAST_CHOICE)
        {
            printf("\n");
            printf("  [!] Invalid option. Please choose from 0 to %d.\n",
                   LOGIN_PORTAL_LAST_CHOICE);

            choice = getInt("  Enter your choice: ");

            if (choice == 0)
                return;
        }

        if (choice == 0)
            return;

        switch (choice)
        {
        case 1:
            teacherLoginPage();
            break;

        case 2:
            studentLoginPage();
            break;

        case 3:
            adminLoginPage();
            break;

        default:
            return;
        }
    }
}