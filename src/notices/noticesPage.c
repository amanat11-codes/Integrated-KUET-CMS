#include <stdio.h>
#include "noticesPage.h"
#include "utility.h"

void showNoticeDetails(Notice n)
{
    clearScreen();

    printf("\n========== NOTICE ==========\n");

    printf("Sl.no : %d\n", n.slNo);
    printf("Title : %s\n", n.title);
    printf("Date  : %s\n", n.date);

    printf("\n%s\n", n.details);

    printf("============================\n");

    printf("\nPress Enter to go back...");

    getchar();//reads the enter key
    getchar();
}


void noticesPage()
{
    Notice notices[2] =
    {
        {1, "ABC", "10-04-2026", "....",
         "Full details of notice ABC go here."},

        {2, "XYZ", "11-05-2026", "....",
         "Full details of notice XYZ go here."}
    };

    int choice;

    while (1)
    {
        clearScreen();

        printf("\n========== NOTICES ==========\n\n");

        printf("1. %s\n", notices[0].title);
        printf("   Date: %s\n", notices[0].date);
        printf("   %s\n\n", notices[0].intro);

        printf("2. %s\n", notices[1].title);
        printf("   Date: %s\n", notices[1].date);
        printf("   %s\n\n", notices[1].intro);

        printf("Enter notice number (0 to go back): ");
        scanf("%d", &choice);

        if (choice == 0)
        {
            return;
        }

        if (choice == 1)
        {
            showNoticeDetails(notices[0]);
        }
        else if (choice == 2)
        {
            showNoticeDetails(notices[1]);
        }
        else
        {
            printf("\nInvalid notice number!\n");
            printf("Press Enter to continue...");
            getchar();
            getchar();
        }
    }
}