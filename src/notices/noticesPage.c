#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "noticesPage.h"
#include "utility.h"
#include <dirent.h>

#define TITLE_PREVIEW_MAX_LENGTH 20
#define DESCRIPTION_PREVIEW_MAX_LENGTH 50

#define NOTICE_DIRECTORY "database/notices"

static int isNoticeFile(const char *filename)
{
    const char *extension = ".notice";
    size_t filenameLength = strlen(filename);
    size_t extensionLength = strlen(extension);

    return filenameLength > extensionLength &&
           strcmp(filename + filenameLength - extensionLength, extension) == 0;
}

int getNoticesCount(void)
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
        if (isNoticeFile(entry->d_name))
            count++;
    }

    closedir(dir);
    return count;
}

int fetchAllNotices(Notice *notices, int count)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(NOTICE_DIRECTORY);
    if (dir == NULL)
    {
        printf("Error: Could not open notices directory.\n");
        return 0;
    }

    int i = 0;
    while (i < count && (entry = readdir(dir)) != NULL)
    {
        if (!isNoticeFile(entry->d_name))
            continue;

        char filePath[256];
        int pathLength = snprintf(filePath, sizeof(filePath), "%s/%s",
                                  NOTICE_DIRECTORY, entry->d_name);
        if (pathLength < 0 || (size_t)pathLength >= sizeof(filePath))
            continue;

        FILE *fp = fopen(filePath, "rb");
        if (fp == NULL)
            continue;

        Notice notice;
        int readSuccessfully = fread(&notice, sizeof(Notice), 1, fp) == 1;
        fclose(fp);

        if (readSuccessfully)
            notices[i++] = notice;
    }

    closedir(dir);
    return i;
}

void generatePreview(char *dest, const char *src, int maxLength)
{
    size_t sourceLength = strlen(src);

    if (maxLength <= 0)
    {
        dest[0] = '\0';
    }
    else if (sourceLength < (size_t)maxLength)
    {
        strcpy(dest, src);
    }
    else
    {
        if (maxLength <= 3)
        {
            for (int i = 0; i < maxLength; i++)
                dest[i] = '.';
            dest[maxLength] = '\0';
            return;
        }

        int prefixLength = maxLength > 3 ? maxLength - 3 : 0;
        strncpy(dest, src, (size_t)prefixLength);
        strcpy(dest + prefixLength, "...");
        dest[maxLength] = '\0';
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
            printf("%s\n%s\n\n%s\n", notices[i].noticeId,
                   showDate(notices[i].date), notices[i].Description);
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
    
    for (int i = 0; i < count; i++)
    {
        char titlePreview[TITLE_PREVIEW_MAX_LENGTH + 1];
        char descriptionPreview[DESCRIPTION_PREVIEW_MAX_LENGTH + 1];

        generatePreview(titlePreview, notices[i].Title, TITLE_PREVIEW_MAX_LENGTH);
        generatePreview(descriptionPreview, notices[i].Description,
                        DESCRIPTION_PREVIEW_MAX_LENGTH);

        printf("%s\t%s\t\t%s\t\t%s\n", notices[i].noticeId,
               showDate(notices[i].date), titlePreview, descriptionPreview);
    }
}

int noticeExists(const char *noticeId)
{
    char filepath[256];
    int pathLength = snprintf(filepath, sizeof(filepath), "%s/%s.notice",
                              NOTICE_DIRECTORY, noticeId);
    if (pathLength < 0 || (size_t)pathLength >= sizeof(filepath))
        return 0;

    FILE *fp = fopen(filepath, "rb");
    if (fp != NULL)
    {
        fclose(fp);
        return 1;
    }

    return 0;
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
    if (notices == NULL)
    {
        printf("Error: Could not allocate memory for notices.\n");
        getCharacter("Press ENTER to go back...\n");
        return;
    }

    count = fetchAllNotices(notices, count);
    if (count == 0)
    {
        free(notices);
        printf("No readable notices found.\n");
        getCharacter("Press ENTER to go back...\n");
        return;
    }

    char choice[5];

    while (1)
    {
        displayNoticeList(notices, count);
        printf("\n");
        printf("\nEnter notice ID to open a notice (0 to go back)\n");
        getString("> ", sizeof(choice), choice);
        
        if (strcmp(choice, "0") == 0)
        {
            free(notices);
            return;
        }

        while(!noticeExists(choice))
        {
            printf("Please input a valid ID from the list\n");
            getString("> ", sizeof(choice), choice);
        }

        showNoticeDetails(notices, choice, count);
    }

    free(notices);
    return;
}