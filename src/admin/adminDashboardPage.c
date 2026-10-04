#include <stdio.h>
#include "addNoticePage.h"
#include "notifications.h"
#include "adminDashboardPage.h"

void adminDashboard()
{
    printf("\tThis is admin dashboard\n");
    
    addNotice();
    viewNotifications();
}