#include "database.h"
#define DATABASE_PATH "database/database.db"
sqlite3* createDatabase()
{
    sqlite3 *db;
    int result = sqlite3_open(DATABASE_PATH, &db);

    if (result != SQLITE_OK)
    {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    printf("Database created successfully.\n");

    return db;
}