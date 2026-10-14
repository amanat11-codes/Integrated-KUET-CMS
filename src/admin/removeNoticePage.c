#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "noticesPage.h"
#include "utility.h"

#define TITLE_INTRO_PREVIEW_MAX_LENGTH 10

void removeNoticePage()
{
    /*
    
    int count = getTableRows(db, "notices");
    Notice *notices = malloc(count * sizeof(Notice));
    if (notices == NULL && count > 0)
    {
        printf("Error: Failed to allocate memory for notices.\n");
        exit(1);
    }
    fetchAllNotices(db, notices);
    
    clearScreen();
    printBoxedText("NOTICES");
    
    int choice;

    while (1)
    {
        displayUpdatedNoticeList(db);
        printf("\n");
        printf("\nEnter notice ID to remove a notice (0 to go back)\n");
        choice = getInt("> ");
        
        if (choice == 0)
        {
            free(notices);
            return;
        }

        while(!noticeExists(db, choice))
        {
            printf("Please input a valid ID from the list\n");
            choice = getInt("> ");
        }

        removeNoticeFromDatabase(db, choice);
    }
    */

    getCharacter("Yet to implement. Press ENTER to go back...\n");
    return;
}