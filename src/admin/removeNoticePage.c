#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "removeNoticePage.h"
#include "noticesPage.h"
#include "utility.h"

#define NOTICE_DIRECTORY "database/notices"
#define NOTICE_ID_LENGTH 4

static int removeNoticeById(const char *noticeId)
{
    char filepath[256];
    int pathLength = snprintf(filepath, sizeof(filepath), "%s/%s.notice",
                              NOTICE_DIRECTORY, noticeId);
    if (pathLength < 0 || (size_t)pathLength >= sizeof(filepath))
        return 0;

    return remove(filepath) == 0;
}

void removeNoticePage(void)
{
    clearScreen();
    printBoxedText("NOTICES");

    int count = getNoticesCount();
    if (count == 0)
    {
        printf("No notices found.\n");
        getCharacter("[?] Press ENTER to go back...\n");
        return;
    }

    Notice *notices = malloc(count * sizeof(Notice));
    if (notices == NULL)
    {
        printf("[!] Error: Could not allocate memory for notices.\n");
        getCharacter("[?] Press ENTER to go back...\n");
        return;
    }

    count = fetchAllNotices(notices, count);
    if (count == 0)
    {
        free(notices);
        printf("No readable notices found.\n");
        getCharacter("[?] Press ENTER to go back...\n");
        return;
    }

    char choice[5];

    while (1)
    {
        displayNoticeList(notices, count);
        printf("\n");
        printf("\nEnter notice ID to remove a notice (0 to go back)\n");
        getString("[?] > ", sizeof(choice), choice);
        
        if (strcmp(choice, "0") == 0)
        {
            free(notices);
            return;
        }

        if (strlen(choice) != NOTICE_ID_LENGTH ||
            isAllDigits(choice) == 0 ||
            !noticeExists(choice))
        {
            printf("Please input a valid notice ID from the list.\n");
            continue;
        }

        if (!removeNoticeById(choice))
        {
            printf("[!] Error: Could not remove notice %s.\n", choice);
            getCharacter("[?] Press ENTER to continue...");
            continue;
        }

        for (int i = 0; i < count; i++)
        {
            if (strcmp(notices[i].noticeId, choice) == 0)
            {
                for (int j = i; j < count - 1; j++)
                    notices[j] = notices[j + 1];
                count--;
                break;
            }
        }

        printf("Notice %s removed successfully.\n", choice);
        if (count == 0)
        {
            getCharacter("[?] Press ENTER to go back...");
            break;
        }

        getCharacter("[?] Press ENTER to refresh the list...");
    }

    free(notices);
    return;
}