#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "noticesPage.h"
#include "utility.h"
#include <dirent.h>

#define TITLE_PREVIEW_MAX_LENGTH 10
#define DESCRIPTION_PREVIEW_MAX_LENGTH 50
#define MAX_NOTICES_PER_PAGE 10

#define NOTICE_DIRECTORY "database/notices"

int getNoticesCount()
{
    DIR *dir;
    struct dirent *entry;
    int count = 0;

    dir = opendir(NOTICE_DIRECTORY);
    if (dir == NULL)
    {
        printf("Error: Could not open notices directory.\n");
        return 0;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strstr(entry->d_name, ".notice") != NULL)
            count++;
    }

    closedir(dir);
    return count;
}


void fetchAllNotices(Notice *notices,int count)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(NOTICE_DIRECTORY);
    if (dir == NULL)
    {
        printf("Error: Could not open notices directory.\n");
        return;
    }

    entry = readdir(dir);
    for (int i = 0; i < count; i++, entry = readdir(dir))
    {
        char filePath[256];
        FILE *fp;

        // if the filename of the current entry does not contain ".notice", skip it
        if (strstr(entry->d_name, ".notice") == NULL)
            continue;

        // construct the full file path by concatenating the directory path and the filename
        snprintf(filePath, sizeof(filePath), "%s/%s", NOTICE_DIRECTORY, entry->d_name);
        

        fp = fopen(filePath, "r");
        if (fp == NULL)
            // if the file cannot be opened, print an error message and continue to the next entry
        {
            printf("Error: Could not open notice file %s.\n", filePath);
            continue;
        }

        // create a new notice struct
        Notice notice;

        // copy the content from the file into the notice struct
        fread(&notice, sizeof(Notice), 1, fp);

        // close the file
        fclose(fp);

        // add the notice to the array
        notices[i] = notice;
    }
    closedir(dir);
}

void generatePreview(char *dest, char *src, int maxLength)
{
    if (strlen(src) <= maxLength)
    {
        strcpy(dest, src);
    }
    else
    {
        strncpy(dest, src, maxLength - 4);
        strcat(dest, "...");
        dest[maxLength - 1] = '\0';
    }
}

void showNoticeDetails(Notice *notices, char *id, int count)
{
    clearScreen();

    for (int i = 0; i < count; i++)
    {
        if (strcmp(notices[i].noticeId, id) == 0)
        {
            printf("\n==================== NOTICE ====================\n");
            printf("%s\n%s\n\n%s\n", notices[i].noticeId, notices[i].date, notices[i].Description);
            printf("================================================\n");
            getCharacter("Press ENTER to go back...");
            clearScreen();
            return;
        }
    }
    printf("Notice not found.\n");
    getCharacter("Press ENTER to go back...");
    clearScreen();
}




void displayNoticeList(Notice *notices, int count)
{
    printf("%s\t%s\t\t%s\t\t%s\n", "ID", "Date", "Title", "Description");
    printf("---------------------------------------------------------\n");
    
    char *dateString;
    char *titlePreview;
    char *descriptionPreview;
    for (register int i = 0; i < count; i++)
    {
        titlePreview = malloc(TITLE_PREVIEW_MAX_LENGTH);
        descriptionPreview = malloc(DESCRIPTION_PREVIEW_MAX_LENGTH);

        showDate(notices[i].date, &dateString);

        if (strlen(notices[i].Title) <= TITLE_PREVIEW_MAX_LENGTH)
            strcpy(titlePreview, notices[i].Title);
        else
            generatePreview(titlePreview, notices[i].Title, TITLE_PREVIEW_MAX_LENGTH);


        if (strlen(notices[i].Description) <= DESCRIPTION_PREVIEW_MAX_LENGTH)
            strcpy(descriptionPreview, notices[i].Description);
        else
            generatePreview(descriptionPreview, notices[i].Description, DESCRIPTION_PREVIEW_MAX_LENGTH);


        //displayNoticeListItem(notices[i].noticeId, dateString, titlePreview, descriptionPreview);

        free(titlePreview);
        free(descriptionPreview);
    }
}

int noticeExists(char *noticeId)
{
    char *filepath = malloc(strlen(NOTICE_DIRECTORY) + strlen(noticeId) + 9); // 8 for "/.notice" and null terminator
    
    snprintf(filepath, sizeof(filepath), "%s/%s.notice", NOTICE_DIRECTORY, noticeId);

    FILE *fp = fopen(filepath, "r");
    if (fp != NULL)
    {
        fclose(fp);
        free(filepath);
        return 1; // Notice exists
    }
    else
    {
        free(filepath);
        return 0; // Notice does not exist
    }
}


void noticesPage()
{
    clearScreen();
    printBoxedText("NOTICES");

    int count = getNoticesCount();
    if (count == 0)
    {
        printf("No notices found.\n");
        getCharacter("Press ENTER to go back...\n");
        return;
    }

    Notice *notices = malloc(count * sizeof(Notice));
    
    fetchAllNotices(notices, count);

    char choice[5];

    while (1)
    {
        displayNoticeList(notices, count);
        printf("\n");
        printf("\nEnter notice ID to open a notice (0 to go back)\n");
        getString("> ", 5, &choice);
        
        if (strcmp(choice, "0") == 0)
        {
            free(notices);
            return;
        }

        while(!noticeExists(choice))
        {
            printf("Please input a valid ID from the list\n");
            getString("> ", 5, &choice);
        }

        showNoticeDetails(notices, choice, count);
    }

    free(notices);
    return;
}