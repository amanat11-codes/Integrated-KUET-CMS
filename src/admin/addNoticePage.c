#include <stdio.h>
#include "addNoticePage.h"
#include "utility.h"

void addNotice()
{
    printBoxedText("You can add notice here");
    // Title
    // Date
    // Body

    char *title = getString("Enter title: ", MAX_TITLE_LENGTH);
    char *date = getString("Enter date: ", MAX_DATE_LENGTH);
    char *body = getString("Enter body: ", MAX_BODY_LENGTH);

    printf("Title: %s\n", title);
    printf("Date: %s\n", date);
    printf("Body: %s\n", body);

    // Amanat
}