#include <stdio.h>
#include <string.h>
#include "database.h"
#include "loginPage.h"
#include "studentDashboard.h"
#include "hallDetailsPage.h"

int main(void)
{
    sqlite3 *db = createDatabase();
    loginPage(db);

    return 0;
}

