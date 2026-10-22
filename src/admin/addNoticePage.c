#include <stdio.h>
#include "addNoticePage.h"
#include "adminDashboardPage.h"
#include "noticesPage.h"
#include "utility.h"
#include <string.h>

#define NOTICE_ID_MAX_LENGTH 5
#define MAX_TITLE_LENGTH 100
#define MAX_DESCRIPTION_LENGTH 512


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


void createNoticeFile(Notice *notice)
{
    char filename[256];
    snprintf(filename, sizeof(filename), "database/notices/%s.notice", notice->noticeId);

    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Error: Could not create notice file at: %s\n", filename);
        return;
    }

    if (fwrite(notice, sizeof(Notice), 1, file) != 1)
    {
        printf("Error: Could not write to notice file at: %s\n", filename);
        fclose(file);
        return;
    } else
        printf("Notice saved successfully to: %s\n", filename);

    fclose(file);
}

static int parseDate(const char *input, int *dd, int *mm, int *yyyy)
{
    char extra;

    if (input == NULL || strlen(input) != 10)
        return 0;

    if (input[2] != '-' || input[5] != '-')
        return 0;

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5)
            continue;

        if (input[i] < '0' || input[i] > '9')
            return 0;
    }

    if (sscanf(input, "%2d-%2d-%4d%c",
               dd, mm, yyyy, &extra) != 3)
        return 0;

    if (*yyyy < 1900 || *yyyy > 9999)
        return 0;

    if (*mm < 1 || *mm > 12)
        return 0;

    if (*dd < 1 || *dd > 31)
        return 0;

    return 1; // return 1 if all checks pass, indicating a valid date
}

void addNotice()
{
    clearScreen();
    printUnderlinedText("Add a Notice");
    
    Notice notice;
    char ch;
    char today[11];

    if (!getTodayDateString(today, sizeof(today)))
    {
        printf("Unable to determine today's date.\n");
        getCharacter("Press ENTER to continue...");
        return;
    }
    
    while (1)
    {
        ch = getCharacter("[?] Do you want to add a new notice? (Y/N): ");
        if (ch == 'N' || ch == 'n')
            return;
        else if (ch != 'Y' && ch != 'y')
        {
            printf("Invalid input. Please enter Y or N.\n");
            continue;
        }
        clearScreen();

        char noticeID[NOTICE_ID_MAX_LENGTH];
        char title[MAX_TITLE_LENGTH];
        char date[MAX_DATE_LENGTH];
        char details[MAX_BODY_LENGTH];
        int dd, mm, yyyy;


        while (1)
        {
            getString("Enter notice ID: ", NOTICE_ID_MAX_LENGTH, noticeID);

            if (noticeID[0] == '\0' || strlen(noticeID) != 4)
            {
                printf("Notice ID must be exactly 4 characters long and cannot be empty. Try again.\n");
                continue;
            }

            snprintf(notice.noticeId, sizeof(notice.noticeId), "%s", noticeID);
            break;
        }


        getString("Enter title: ", MAX_TITLE_LENGTH, title);

        while (1)
        {
            getString("Enter date (dd-mm-yyyy; leave blank for today's date): ",
                      MAX_DATE_LENGTH, date);
            if (date[0] == '\0')
                snprintf(date, sizeof(date), "%s", today);

            if (parseDate(date, &dd, &mm, &yyyy))
            {
                notice.date.day = dd;
                notice.date.month = mm;
                notice.date.year = yyyy;
                break;
            }
            else
            {
                printf("Invalid date format. Please enter in dd-mm-yyyy format.\n");
            }

        }

        getString("Enter details: ", MAX_BODY_LENGTH, details);
        strcpy(notice.Title, title);
        strcpy(notice.Description, details);

        createNoticeFile(&notice);
        printf("Notice added successfully!\n");
        getCharacter("Press ENTER to continue...");
    }
 
}