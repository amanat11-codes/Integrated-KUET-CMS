#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "noticesPage.h"
#include "utility.h"
#include "sqlite3.h"

#define TITLE_INTRO_PREVIEW_MAX_LENGTH 10

void removeNoticeFromDatabase(sqlite3 *db, int id)
{
    clearScreen();

    char *sql = "DELETE FROM notices WHERE notice_id = ?;";
    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        printf("Notice removed successfully.\n");
        getCharacter("Press ENTER to go back...");
    } else
    {
        printf("Failed to remove notice.\n");
        printf("================================================\n");
    }

    clearScreen();
}

void displayUpdatedNoticeList(sqlite3 *db)
{
    char *sql = "SELECT * FROM notices;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    Notice n;
    // Execute the query and display the results
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        n.id = sqlite3_column_int(stmt, 0);
        strcpy(n.date, (const char *) sqlite3_column_text(stmt, 1));
        strcpy(n.title, (const char *) sqlite3_column_text(stmt, 2));
        strcpy(n.intro, (const char *) sqlite3_column_text(stmt, 3));
        displayNoticeListItem(n.id, n.date, n.title, n.intro);
    }
    sqlite3_finalize(stmt);
}


void removeNoticePage(sqlite3 *db)
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
        displayUpdatedNoticeList(db);
        printf("\n");
        printf("\nEnter notice ID to remove a notice (0 to go back)\n");
        choice = getInt("> ");
        
        if (choice == 0)
        {
            free(notices);
            return;
        }

        while(!noticeExists(db, choice))
        {
            printf("Please input a valid ID from the list\n");
            choice = getInt("> ");
        }

        removeNoticeFromDatabase(db, choice);
    }
}


// TODO:
// UPDATE THE DISPLAYING NOTICE LIST LOGIC IN REMOVE-NOTICE-PAGE (ADMIN)
// AND NOTICES-PAGE (GENERAL)