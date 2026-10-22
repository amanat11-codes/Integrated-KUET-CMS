#include <stdio.h>
#include <string.h>
#include "mainMenu.h"
#include "noticesPage.h"
#include "studentLoginPage.h"
#include "teacherLoginPage.h"
#include "adminLoginPage.h"
#include "studentRegistrationPage.h"
#include "teacherRegistrationPage.h"
#include "adminRegistrationPage.h"

void invalidCommandLineArgs(char *appName)
{
    printf("[!] ERROR: Invalid command line arguments.\n");
    printf("Usage: ./%s [notices]\n", appName);
    printf("Alt: ./%s [login|register] [teacher|student|admin]\n", appName);
}

int main(int argc, char *argv[])
{

    switch (argc)
    {
    case 1:
    {
        mainMenu();
        return 0;
    }
    case 2:
    {
        if (strcmp(argv[1], "notices") == 0 ||
            strcmp(argv[1], "Notices") == 0 ||
            strcmp(argv[1], "NOTICES") == 0)
        {
            noticesPage();
            break;
        }

        invalidCommandLineArgs("app");
        return 1;
    }
    case 3:
    {
        if (strcmp(argv[1], "login") == 0 ||
            strcmp(argv[1], "Login") == 0 ||
            strcmp(argv[1], "LOGIN") == 0)
        {
            if (strcmp(argv[2], "teacher") == 0 ||
                strcmp(argv[2], "Teacher") == 0 ||
                strcmp(argv[2], "TEACHER") == 0)
            {
                teacherLoginPage();
                break;
            }
            else if (strcmp(argv[2], "student") == 0 ||
                     strcmp(argv[2], "Student") == 0 ||
                     strcmp(argv[2], "STUDENT") == 0)
            {
                studentLoginPage();
                break;
            }
            else if (strcmp(argv[2], "admin") == 0 ||
                     strcmp(argv[2], "Admin") == 0 ||
                     strcmp(argv[2], "ADMIN") == 0)
            {
                adminLoginPage();
                break;
            }
            else
            {
                invalidCommandLineArgs("app");
                return 1;
            }
        }
        else if (strcmp(argv[1], "register") == 0 ||
                 strcmp(argv[1], "Register") == 0 ||
                 strcmp(argv[1], "REGISTER") == 0)
        {
            if (strcmp(argv[2], "teacher") == 0 ||
                strcmp(argv[2], "Teacher") == 0 ||
                strcmp(argv[2], "TEACHER") == 0)
            {
                teacherRegistrationPage();
                break;
            }
            else if (strcmp(argv[2], "student") == 0 ||
                     strcmp(argv[2], "Student") == 0 ||
                     strcmp(argv[2], "STUDENT") == 0)
            {
                studentRegistrationPage();
                break;
            }
            else if (strcmp(argv[2], "admin") == 0 ||
                     strcmp(argv[2], "Admin") == 0 ||
                     strcmp(argv[2], "ADMIN") == 0)
            {
                adminRegistrationPage();
                break;
            }
            else
            {
                invalidCommandLineArgs("app");
                return 1;
            }
        }
        else
        {
            invalidCommandLineArgs("app");
            return 1;
        }
        break;
    }
    }
    mainMenu();
    return 0;
}
