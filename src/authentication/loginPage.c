#include <stdio.h>
#include <stdlib.h>
#include "loginPage.h"
#include "studentLoginPage.h"
#include "teacherLoginPage.h"
#include "adminLoginPage.h"
#include "noticesPage.h"
#include "utility.h"

#define CHOICE_LAST 5

void loginPage(sqlite3 *db)
{
    int choice;
    while (1)
    {
        clearScreen();
        printf("1. Student Login\n");
        printf("2. Teacher Login\n");
        printf("3. Admin Login\n");
        printf("4. Show Notices\n");
        printf("5. Quit\n");

        choice = getInt("> ");

        while (!(choice >= 1 && choice <= CHOICE_LAST))
        {
            printf("Please input a valid option, between 1 and %d\n", CHOICE_LAST);
            choice = getInt("> ");
        }

    switch(choice)
        {
            case 1:
                studentLoginPage();
                break;

            case 2:
                teacherLoginPage();
                break;

            case 3:
                adminLoginPage(db);
                break;

            case 4:
                noticesPage(db);
                break;

            case 5:
                printf("Exiting...\n");
                sqlite3_close(db);
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
}
