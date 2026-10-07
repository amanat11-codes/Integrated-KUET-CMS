#include <stdio.h>
#include "loginPage.h"
#include "database.h"
#include "sqlite3.h"
void showLoginPage(sqlite3 *db)
{
    loginPage(db);
}

int main(void)
{
    sqlite3 *db = createDatabase();
    
    showLoginPage(db);

    // reduce function calls on the stack
    return 0;
}