#include <stdio.h>
#include <stdlib.h>
#include "studentDashboard.h"
#include "studentProfilePage.h"
#include "hallDetailsPage.h"
#include "academicInfoPage.h"
#include "libraryInfoPage.h"
#include "teacherProfilePage.h"
#include "utility.h"

#define LAST_CHOICE 6

void studentDashboard()
{
    while (1)
    {
        clearScreen();
        printBoxedText("STUDENT DASHBOARD PANEL");
        printf("1. View profile\n");
        printf("2. View hall details\n");
        printf("3. View academic information\n");
        printf("4. View library information\n");
        printf("5. View teacher profile\n");
        printf("6. Quit\n");

        int choice;
        while ((choice = getInt("> ")) < 1 || choice > LAST_CHOICE)
        {
            printf("Invalid choice. Please try again.\n");
        }

        switch (choice)
        {
            case 1:
                studentProfilePage();
                break;
            case 2:
                hallDetailsPage();
                break;
            case 3:
                academicInfoPage();
                break;
            case 4:
                libraryInfoPage();
                break;
            case 5:
                teacherProfilePage();
                break;
            case 6:
                printf("Quitting...\n");
                exit(0);
        }
    }
}