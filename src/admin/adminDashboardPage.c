#include <stdio.h>
#include "addNoticePage.h"
#include "notifications.h"
#include "adminDashboardPage.h"
#include "utility.h"

#define LAST_CHOICE 3

void adminDashboard()
{
    while (1)
    {    
        clearScreen();
        printBoxedText("ADMIN DASHBOARD PANEL");
        printf("1. Add notice\n");
        printf("2. View notifications\n");
        printf("3. Quit\n");
        //printf("3. Logout");

        int choice;
        while ( (choice = getInt("> ")) < 1 || choice > LAST_CHOICE)
        {
            printf("Invalid choice. Please try again.\n");
        }
        
        switch(choice)
        {
            case 1:
                addNotice();
                break;
            case 2:
                viewNotifications();
                break;
            case 3:
                printf("Quitting...\n");
                return;
        }
    }
}