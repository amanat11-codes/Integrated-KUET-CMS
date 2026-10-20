#ifndef TEACHER_PROFILE_PAGE_H
#define TEACHER_PROFILE_PAGE_H

typedef struct {
    char name[80];
    char teacherId[9];
    char designation[20];
    char department[50];
    char phone[16];
    char email[80];
    char researchInterest[160];
} TeacherProfile;

void teacherProfilePage(const char *teacherId, const char *filepath);
void showTeacherProfile(const TeacherProfile *record,
                               const char *teacherId);

#endif