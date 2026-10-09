#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "noticesPage.h"
#include "utility.h"
#include "sqlite3.h"

#define TITLE_INTRO_PREVIEW_MAX_LENGTH 10

void displayNoticeListItem(int serial, char* date, char* title, char* intro)
{
    printf("%d\t%s\t", serial,date);
    
    if(strlen(title) > TITLE_INTRO_PREVIEW_MAX_LENGTH)
        printf("%.*s...", TITLE_INTRO_PREVIEW_MAX_LENGTH, title);
    else
        printf("%s", title);
    printf("\t");
    if (strlen(intro) > TITLE_INTRO_PREVIEW_MAX_LENGTH)
        printf("%.*s...", TITLE_INTRO_PREVIEW_MAX_LENGTH, intro);
    else
        printf("%s", intro);
    printf("\n");
}

void showNoticeDetails(sqlite3 *db, int id)
{
    clearScreen();

    char *sql = "SELECT * FROM notices WHERE notice_id = ?;";
    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        printf("\n==================== NOTICE ====================\n");
        printf("%s\n%s\n\n%s\n", sqlite3_column_text(stmt, 1), sqlite3_column_text(stmt, 2), sqlite3_column_text(stmt, 4));
        printf("================================================\n");
        getCharacter("Press ENTER to go back...");
    } else
    {
        printf("\n==================== NOTICE ====================\n");
        printf("Notice not found\n");
        getCharacter("Press ENTER to go back...");
        printf("================================================\n");
    }

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
        notices[i].id = sqlite3_column_int(stmt, 0);
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
    printf("%s\t%s\t\t%s\t\t%s\n", "ID", "Date", "Title", "Description");
    printf("---------------------------------------------------------\n");
    for (register int i = 0; i < count; i++)
        displayNoticeListItem(notices[i].id, notices[i].date, notices[i].title, notices[i].intro);
}

int noticeExists(sqlite3 *db, int noticeId)
{
    char *sql = "SELECT EXISTS (SELECT 1 FROM NOTICES WHERE notice_id = ?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, noticeId);
    int exists = 0;

    if (sqlite3_step(stmt) == SQLITE_ROW)
        exists = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return exists;
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
        printf("\n");
        printf("\nEnter notice ID to open a notice (0 to go back)\n");
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

        showNoticeDetails(db, choice);
    }
}