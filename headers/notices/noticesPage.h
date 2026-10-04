void noticesPage();
#ifndef NOTICES_PAGE_H
#define NOTICES_PAGE_H

typedef struct {
    int  slNo;
    char title[50];
    char date[15];
    char intro[100];
    char details[500];
} Notice;

void noticesPage();
void showNoticeDetails(Notice n);

#endif