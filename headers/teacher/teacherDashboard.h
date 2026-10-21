#ifndef TEACHER_DASHBOARD_H
#define TEACHER_DASHBOARD_H

#include <stdint.h>

typedef struct {
    char name[80];
    char teacherId[9];
    char designation[20];
    char department[50];
    char phone[16];
    char email[80];
    char researchSpecialization[160];
} TeacherProfile;

typedef struct {
    uint32_t teacherProfileOffset;
    uint32_t taughtCoursesOffset;
    uint32_t taughtCourseCount;
} TeacherFileHeader;

typedef struct {
    char courseName[12];
} TaughtCourse;

typedef struct {
    uint32_t studentCount;
} CourseFileHeader;

typedef struct {
    char studentId[9];
} CourseEnrollment;


void teacherDashboard(const char *teacherId, const char *filepath);

#endif