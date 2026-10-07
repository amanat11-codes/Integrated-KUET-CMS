#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "noticesPage.h"
#include "utility.h"
#include "sqlite3.h"

void displayNoticeListItem(int serial, char* date, char* title, char* intro)
{
    printf("%d\t\t%s\t\t%s\t\t%s\n", serial, date, title, intro);
}

void showNoticeDetails(Notice n)
{
    clearScreen();
    
    printf("\n==================== NOTICE ====================\n");
    printf("%s\n%s\n%s\n", n.date, n.title, n.details);
    printf("================================================\n");
    getCharacter("Press ENTER to go back...");
    clearScreen();
}

void fetchAllNotices(sqlite3 *db, Notice *notices)
{
    char *sql = "SELECT * FROM notices;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    int i = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        notices[i].slNo = sqlite3_column_int(stmt, 0);
        if ((char*)sqlite3_column_text(stmt, 1) != NULL)
            strcpy(notices[i].date, (char*)sqlite3_column_text(stmt, 1));
        else
            strcpy(notices[i].date, "N/A");
        
        if ((char*)sqlite3_column_text(stmt, 2) != NULL)
            strcpy(notices[i].title, (char*)sqlite3_column_text(stmt, 2));
        else
            strcpy(notices[i].title, "N/A");
        if ((char*)sqlite3_column_text(stmt, 3) != NULL)
            strcpy(notices[i].intro, (char*)sqlite3_column_text(stmt, 3));
        else
            strcpy(notices[i].intro, "N/A");
        if ((char*)sqlite3_column_text(stmt, 4) != NULL)
            strcpy(notices[i].details, (char*)sqlite3_column_text(stmt, 4));
        else
            strcpy(notices[i].details, "N/A");
        i++;
    }
    sqlite3_finalize(stmt);
}

void displayNoticeList(Notice *notices, int count)
{
    printf("%-5s%-15s%-25s%s\n", "ID", "Date", "Title", "Desc");
    printf("-------------------------------------------------------------------------------------\n");
    for (register int i = 0; i < count; i++)
        printf("%-5d%-15s%-25s%s\n", notices[i].slNo, notices[i].date, notices[i].title, notices[i].intro);

}

void noticesPage(sqlite3 *db)
{
    int count = getTableRows(db, "notices");
    Notice *notices = malloc(count * sizeof(Notice));
    if (notices == NULL && count > 0)
    {
        printf("Error: Failed to allocate memory for notices.\n");
        exit(1);
    }
    fetchAllNotices(db, notices);
    
    clearScreen();
    printBoxedText("NOTICES");
    
    int choice;

    while (1)
    {
        displayNoticeList(notices, count);
        printf("\nEnter Sl.no to open a notice (0 to go back)\n");
        choice = getInt("> ");

        while (!(choice >= 0 && choice <= count))
        {
            printf("Please input a valid option, between 1 and %d\n", count);
            choice = getInt("> ");
        }

        if (choice == 0)
        {
            free(notices);
            return;
        }

        showNoticeDetails(notices[choice - 1]);
    }
}