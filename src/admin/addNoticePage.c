#include <stdio.h>
#include "addNoticePage.h"
#include "adminDashboardPage.h"
#include "noticesPage.h"
#include "utility.h"
#include <string.h>

char* createIntro(char* details)
{
    static char intro[MAX_INTRO_SIZE];
    int detailsLength = strlen(details);
    int prefixLength = MAX_INTRO_SIZE - 1 - 3;

    if (detailsLength <= prefixLength)
        strcpy(intro, details);
    else
        snprintf(intro, MAX_INTRO_SIZE, "%.*s...", prefixLength, details);

    return intro;

}

void insertNoticeToDatabase(sqlite3 *db, Notice *notice)
{
    const char *sql =
        "INSERT INTO notices (date, title, intro, details) "
        "VALUES (?, ?, ?, ?);";
    sqlite3_stmt *stmt = NULL;
    int result;

    result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare notice insert: %s\n",
                sqlite3_errmsg(db));
        return;
    }

    result = sqlite3_bind_text(stmt, 1, notice->date, -1, SQLITE_TRANSIENT);
    if (result == SQLITE_OK)
        result = sqlite3_bind_text(stmt, 2, notice->title, -1, SQLITE_TRANSIENT);
    if (result == SQLITE_OK)
        result = sqlite3_bind_text(stmt, 3, notice->intro, -1, SQLITE_TRANSIENT);
    if (result == SQLITE_OK)
        result = sqlite3_bind_text(stmt, 4, notice->details, -1, SQLITE_TRANSIENT);

    if (result == SQLITE_OK)
        result = sqlite3_step(stmt);

    if (result == SQLITE_DONE)
        printf("Notice added successfully.\n");
    else
        fprintf(stderr, "Failed to add notice: %s\n",
                sqlite3_errmsg(db));
    
    sqlite3_finalize(stmt);
}

void addNotice(sqlite3 *db)
{
    clearScreen();
    printUnderlinedText("Add a Notice");
    
    Notice notice;
    char ch;

    while ((ch = getCharacter("Press ENTER to add a notice or ANY other key to go back...\n")) == '\n')
    {
        clearScreen();  
        getString("Enter title: ", MAX_TITLE_LENGTH, notice.title);
        getString("Enter date: ", MAX_DATE_LENGTH, notice.date);
        getString("Enter details: ", MAX_BODY_LENGTH, notice.details);

        strcpy(notice.intro, createIntro(notice.details));

        insertNoticeToDatabase(db, &notice);
    }
}