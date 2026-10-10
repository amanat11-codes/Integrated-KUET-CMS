

#include <stdio.h>
#include <windows.h>
#include <sqlite3.h>

#include "studentLoginPage.h"

#define DB_NAME "database/kuet_cms.db"

static void openStudentDashboardWindow(const char *student_id)
{
    char exePath[MAX_PATH];
    char commandLine[MAX_PATH + 300];

    STARTUPINFOA si = {0};
    PROCESS_INFORMATION pi = {0};

    si.cb = sizeof(si);

    DWORD len = GetModuleFileNameA(
        NULL, exePath, MAX_PATH
    );

    if (len == 0 || len >= MAX_PATH)
    {
        printf("Cannot locate the application.\n");
        return;
    }

    snprintf(
        commandLine,
        sizeof(commandLine),
        "\"%s\" --student-dashboard \"%s\"",
        exePath,
        student_id
    );

    BOOL success = CreateProcessA(
        exePath,
        commandLine,
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si,
        &pi
    );

    if (!success)
    {
        printf("Cannot open Dashboard Window. Error: %lu\n",
               GetLastError());
        return;
    }

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
}

void studentLoginPage(void)
{
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;

    char student_id[100];
    char password[100];

    printf("\n========== STUDENT LOGIN ==========\n");

    printf("Enter Student ID: ");

    if (scanf("%99s", student_id) != 1)
        return;

    printf("Enter Password: ");

    if (scanf("%99s", password) != 1)
        return;

    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK)
    {
        printf("Database connection failed: %s\n",
               db ? sqlite3_errmsg(db) : "Unknown error");

        if (db != NULL)
            sqlite3_close(db);

        return;
    }

    const char *sql =
        "SELECT 1 FROM students "
        "WHERE student_id = ? AND password = ?";

    if (sqlite3_prepare_v2(
            db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("SQL error: %s\n", sqlite3_errmsg(db));

        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(
        stmt, 1, student_id, -1, SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        stmt, 2, password, -1, SQLITE_TRANSIENT
    );

    int rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        sqlite3_close(db);

        printf("\nLogin successful!\n");
        printf("Opening Student Dashboard...\n");

        openStudentDashboardWindow(student_id);
        return;
    }

    if (rc == SQLITE_DONE)
    {
        printf("\nInvalid Student ID or Password.\n");
    }
    else
    {
        printf("Database query failed: %s\n",
               sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
