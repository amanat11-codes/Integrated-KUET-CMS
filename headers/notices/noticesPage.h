
void noticesPage();
#ifndef NOTICES_PAGE_H
#define NOTICES_PAGE_H

#define MAX_TITLE_LENGTH 100
#define MAX_DATE_LENGTH 20
#define MAX_BODY_LENGTH 500
#define MAX_INTRO_SIZE (MAX_BODY_LENGTH / 10)
typedef struct {
    int  slNo;
    char title[MAX_TITLE_LENGTH];
    char date[MAX_DATE_LENGTH];
    char intro[MAX_INTRO_SIZE];
    char details[MAX_BODY_LENGTH];
} Notice;

void noticesPage();
void showNoticeDetails(Notice n);

#endif