#include <stdio.h>
#include "addNoticePage.h"
#include "adminDashboardPage.h"
#include "noticesPage.h"
#include "utility.h"
#include <string.h>

char* createIntro(char* details)
{
    static char intro[MAX_INTRO_SIZE];
    int detailsLength = strlen(details);
    int prefixLength = MAX_INTRO_SIZE - 1 - 3;

    if (detailsLength <= prefixLength)
        strcpy(intro, details);
    else
        snprintf(intro, MAX_INTRO_SIZE, "%.*s...", prefixLength, details);

    return intro;

}

void addNotice()
{
    clearScreen();
    printUnderlinedText("Add a Notice");
    
    Notice notice;
    char ch;

    while ((ch = getCharacter("Press ENTER to add a notice or ANY other key to go back...\n")) == '\n')
    {
        clearScreen();  
        getString("Enter title: ", MAX_TITLE_LENGTH, notice.title);
        getString("Enter date: ", MAX_DATE_LENGTH, notice.date);
        getString("Enter details: ", MAX_BODY_LENGTH, notice.details);

        strcpy(notice.intro, createIntro(notice.details));

        printf("Title: %s\n", notice.title);
        printf("Date: %s\n", notice.date);
        printf("Intro: %s\n", notice.intro);
        printf("Body: %s\n", notice.details);
    }
}