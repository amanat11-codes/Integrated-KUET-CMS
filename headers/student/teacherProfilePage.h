#ifndef TEACHER_PROFILE_PAGE_H
#define TEACHER_PROFILE_PAGE_H

#include "teacherDashboard.h"

void teacherProfilePage(const char *teacherId, const char *filepath);
void showTeacherProfile(const TeacherProfile *record,
                               const char *teacherId);

#endif