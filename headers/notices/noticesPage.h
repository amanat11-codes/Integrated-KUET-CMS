#ifndef NOTICES_PAGE_H
#define NOTICES_PAGE_H

#include "utility.h"

#define MAX_TITLE_LENGTH 100
#define MAX_DATE_LENGTH 20
#define MAX_BODY_LENGTH 1000
#define MAX_INTRO_SIZE (MAX_BODY_LENGTH / 10)

typedef struct {
    char noticeId[5];
    Date date;
    char Title[100];
    char Description[512];
} Notice;

int getNoticesCount(void);
int fetchAllNotices(Notice *notices, int count);
void displayNoticeList(Notice *notices, int count);
int noticeExists(const char *noticeId);
void noticesPage(void);

#endif