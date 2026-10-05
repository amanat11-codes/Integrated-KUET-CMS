#include <stdio.h>
#include "addNoticePage.h"
#include "adminDashboardPage.h"
#include "utility.h"

void addNotice()
{
    clearScreen();
    printUnderlinedText("Add a Notice");
    // Title
    // Date
    // Body

    
    char title[MAX_TITLE_LENGTH];
    char date[MAX_DATE_LENGTH];
    char body[MAX_BODY_LENGTH];



    char ch;

    while ((ch = getCharacter("Press ENTER to add a notice or ANY other key to go back...\n")) == '\n')
    {  
        getString("Enter title: ", MAX_TITLE_LENGTH, title);
        getString("Enter date: ", MAX_DATE_LENGTH, date);
        getString("Enter body: ", MAX_BODY_LENGTH, body);

        printf("Title: %s\n", title);
        printf("Date: %s\n", date);
        printf("Body: %s\n", body);
    }

    // Amanat
}