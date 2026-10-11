#include "utility.h"
#include <stdio.h>
#include <windows.h>
#include <sqlite3.h>
#include "studentLoginPage.h"
#include "studentDashboard.h"
#define STUDENT_ID_AND_PASSWORD_MAX_LENGTH 8 // excluding null terminator



int studentAccountExists(sqlite3 *db, const char *student_id, const char *password)
{
    const char *sql = "SELECT COUNT(*) FROM students WHERE student_id = ? AND password = ?";
    sqlite3_stmt *stmt;
    int count = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, student_id, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            count = sqlite3_column_int(stmt, 0);
        }

        sqlite3_finalize(stmt);
    }

    return count > 0; // Return 1 if account exists, 0 otherwise
}

void studentLoginPage(sqlite3 *db)
{
    char student_id[STUDENT_ID_AND_PASSWORD_MAX_LENGTH + 1]; // +1 for null terminator
    char password[STUDENT_ID_AND_PASSWORD_MAX_LENGTH + 1];

    while (1)
    {
        clearScreen();
        printBoxedText("STUDENT LOGIN");
        getString("Enter Student ID: ", sizeof(student_id), student_id);
        getString("Enter Password: ", sizeof(password), password);

        if (strlen(student_id) != STUDENT_ID_AND_PASSWORD_MAX_LENGTH || strlen(password) != STUDENT_ID_AND_PASSWORD_MAX_LENGTH)
        {
            printf("\nStudent ID and Password must be %d characters long.\n", STUDENT_ID_AND_PASSWORD_MAX_LENGTH);
            printf("Size of student_id: %lld\n", strlen(student_id));
            printf("Size of password: %lld\n", strlen(password));
            getCharacter("Press ENTER to try again...");
            continue;
        }

       if (!studentAccountExists(db, student_id, password))
        {
            printf("\nInvalid Student ID or Password.\n");
            getCharacter("Press ENTER to try again...");

            continue;
        } else {
            printf("\nLogin successful! Press any key to proceed...\n");
            getCharacter("Press ENTER to continue...");

        }

        studentDashboard(db, student_id);
    }
}
