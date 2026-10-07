#include "sqlite3.h"



void noticesPage(sqlite3 *db);
#ifndef NOTICES_PAGE_H
#define NOTICES_PAGE_H

#define MAX_TITLE_LENGTH 100
#define MAX_DATE_LENGTH 20
#define MAX_BODY_LENGTH 1000
#define MAX_INTRO_SIZE (MAX_BODY_LENGTH / 10)
typedef struct {
    int  slNo;
    char title[MAX_TITLE_LENGTH];
    char date[MAX_DATE_LENGTH];
    char intro[MAX_INTRO_SIZE];
    char details[MAX_BODY_LENGTH];
} Notice;

void showNoticeDetails(Notice n);
void fetchAllNotices(sqlite3 *db, Notice *notices);
void displayNoticeListItem(int serial, char* date, char* title, char* intro);
void displayNoticeList(Notice *notices, int count);
int noticeExists(sqlite3 *db, int noticeId);


#endif