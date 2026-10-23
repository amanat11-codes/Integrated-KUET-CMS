#include <stdio.h>
#include "loginPortal.h"
#include "studentLoginPage.h"
#include "teacherLoginPage.h"
#include "adminLoginPage.h"
#include "utility.h"

#define LOGIN_PORTAL_LAST_CHOICE 3

void loginPortal(void)
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
        printf("\n");

        printf("----------------------------------------------------------------\n");
        printf("                    SELECT ACCOUNT TYPE                         \n");
        printf("----------------------------------------------------------------\n");

        printf("\n");

        printMenuItems(
            LOGIN_PORTAL_LAST_CHOICE,
            "Teacher Login",
            "Student Login",
            "Admin Login");

        printf("\n");
        printf("----------------------------------------------------------------\n");
        printf("  0. Back to Main Menu                                           \n");
        printf("----------------------------------------------------------------\n");

        printf("\n");

        while (1)
        {
            choice = getInt("  [?] Enter your choice: ");
            if (choice < 0 || choice > LOGIN_PORTAL_LAST_CHOICE)
                continue;

            if (choice == 0)
                return;

            break;
        }
        while (getchar() != '\n'); // Clear the input buffer
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