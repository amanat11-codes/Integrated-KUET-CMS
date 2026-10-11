#include "database.h"
#define DATABASE_PATH "database/database.db"
sqlite3* createDatabase()
{
    sqlite3 *db;
    int result = sqlite3_open(DATABASE_PATH, &db);

    if (result != SQLITE_OK)
    {
        // error opening db
        sqlite3_close(db);
        exit(1);
    }

    // successfully opened db

    

    return db;
}