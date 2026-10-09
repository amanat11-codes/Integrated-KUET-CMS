#include <stdio.h>
#include "loginPage.h"
#include "database.h"
#include "sqlite3.h"


int main(void)
{
    sqlite3 *db = createDatabase();
    
    loginPage(db);

    // reduce function calls on the stack
    return 0;
}