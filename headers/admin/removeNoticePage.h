#include "sqlite3.h"

void removeNoticePage(sqlite3 *db);
void removeNoticeFromDatabase(sqlite3 *db, int noticeId);
void displayUpdatedNoticeList(sqlite3 *db);
