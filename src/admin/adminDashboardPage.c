#include <stdio.h>
#include <stdlib.h>
#include "addNoticePage.h"
#include "notifications.h"
#include "adminDashboardPage.h"
#include "removeNoticePage.h"
#include "utility.h"
#include "sqlite3.h"

#define LAST_CHOICE 5

void adminDashboard(sqlite3 *db)
{
    while (1)
    {    
        clearScreen();
        printBoxedText("ADMIN DASHBOARD PANEL");
        printf("1. Add notice\n");
        printf("2. Remove notice\n");
        printf("3. View notices\n");
        printf("4. View notifications\n");
        printf("5. Quit\n");

        int choice;
        while ( (choice = getInt("> ")) < 1 || choice > LAST_CHOICE)
        {
            printf("Invalid choice. Please try again.\n");
        }
        
        switch(choice)
        {
            case 1:
                addNotice(db);
                break;
            case 2:
                removeNoticePage(db);
                break;
            case 3:
                noticesPage(db);
                break;
            case 4:
                viewNotifications();
                break;
            case 5:
                printf("Quitting...\n");
                sqlite3_close(db);
                exit(0);
        }
    }
}