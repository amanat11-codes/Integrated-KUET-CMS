
#include <stdio.h>
#include <string.h>

#include "authentication/loginPage.h"
#include "student/studentDashboard.h"
#include "student/hallDetailsPage.h"

int main(int argc, char *argv[])
{
    if (argc >= 3 &&
        strcmp(argv[1], "--student-dashboard") == 0)
    {
        studentDashboard(argv[2]);
        return 0;
    }

    if (argc >= 3 &&
        strcmp(argv[1], "--hall-details") == 0)
    {
        hallDetailsPage(argv[2]);
        return 0;
    }

    loginPage();

    return 0;
}

