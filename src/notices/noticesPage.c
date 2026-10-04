#include <stdio.h>
#include "noticesPage.h"

void showNoticeDetails(Notice n)
{
    printf("\n==================== NOTICE ====================\n");
    printf("Sl.no : %d\n", n.slNo);
    printf("Title : %s\n", n.title);
    printf("Date  : %s\n", n.date);
    printf("------------------------------------------------\n");
    printf("%s\n", n.details);
    printf("================================================\n");
    printf("\nPress Enter to go back...");
    while (getchar() != '\n');
    getchar();
}

void noticesPage()
{
    printf("This is notices page\n");

    // anyone can check notices here
    
    // sl.no
    // title
    // date
    // short intro
    // sl.no title date short intro
    // 1    ABC    10-4-2026    ....
    // 2    XYZ    11-05-2025   ....

    Notice notices[] = {
        {1, "ABC", "10-4-2026",  "....", "Full details of notice ABC go here."},
        {2, "XYZ", "11-05-2025", "....", "Full details of notice XYZ go here."}
    };
    int count = sizeof(notices) / sizeof(notices[0]);
    int choice;

    while (1)
    {
        printf("\n%-6s %-20s %-12s %s\n", "Sl.no", "Title", "Date", "Short intro");
        printf("------------------------------------------------------\n");

        for (int i = 0; i < count; i++)
        {
            printf("%-6d %-20s %-12s %s\n",
                   notices[i].slNo, notices[i].title,
                   notices[i].date, notices[i].intro);
        }

        printf("\nEnter Sl.no to open a notice (0 to go back): ");
        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            continue;
        }

        if (choice == 0)
            return;

        int found = 0;
        for (int i = 0; i < count; i++)
        {
            if (notices[i].slNo == choice)
            {
                showNoticeDetails(notices[i]);
                found = 1;
                break;
            }
        }

        if (!found)
            printf("No notice with Sl.no %d. Try again.\n", choice);
    }
}