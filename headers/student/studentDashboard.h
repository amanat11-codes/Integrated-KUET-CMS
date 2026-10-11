#ifndef STUDENT_DASHBOARD_H
#define STUDENT_DASHBOARD_H

#include <sqlite3.h>

void studentDashboard(sqlite3 *db, char *student_id);
int studentAccountExists(sqlite3 *db, const char *student_id, const char *password);

void showStudentProfilePage();
void showHallDetailsPage();
void showAcademicInfoPage();
void showLibraryInfoPage();
void showTeacherInfoPage();
#endif