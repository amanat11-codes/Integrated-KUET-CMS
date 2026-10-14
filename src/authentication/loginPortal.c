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
        printBoxedText("LOGIN PORTAL");
        printUnderlinedText("Choose an account type");
        printMenuItems(
            LOGIN_PORTAL_LAST_CHOICE,
            "Teacher Login",
            "Student Login",
            "Admin Login");
        printf("0. Back\n");

        choice = getInt("> ");

        while (choice < 0 || choice > LOGIN_PORTAL_LAST_CHOICE)
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