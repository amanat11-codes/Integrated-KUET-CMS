#ifndef ADD_NOTICE_PAGE_H
#define ADD_NOTICE_PAGE_H

#include "sqlite3.h"
#include "noticesPage.h"

void addNotice(sqlite3 *db);
char* createIntro(char* details);
void insertNoticeToDatabase(sqlite3 *db, Notice *notice);

#endif