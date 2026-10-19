#ifndef STUDENT_DASHBOARD_H
#define STUDENT_DASHBOARD_H
#include <stdint.h>
#include "utility.h"

typedef struct {
    char courseCode[5];
    char courseShortName[12];
    char courseTitle[30];
    float gradePoint;
    float courseCredit;
    char letterGrade[3];
} Course;

typedef struct{
    char name[80];
    int session;
    char departmentName[50];
    char departmentShortName[10];
    int year;
    int term;
    float creditTaken;
    float creditCompleted;
    float termGPA;
    float cgpa;
    Course courses[8];
} AcademicRecord;

typedef struct {
    char name[80];
    char department[50];
    char year[12];
    char term[12];
    char phone[16];
    char email[80];
    char bloodGroup[4];
    char fathersName[80];
    char mothersName[80];
    char permanentAddress[160];
    char currentAddress[160];
    char advisor[80];
} StudentProfile;

typedef struct {
    char hallName[50];
    int mealStatus;
    int boarderNumber;
    char hallSide[10];
    Date nextMonthlyFeast;
    int setMeal;
    char offStartDate[11]; 
    char offEndDate[11];
} HallDetails;

typedef struct {
    char bookTitle[80];
    Date returnDate;
} IssuedBook;

typedef struct {
    int bookCount;
    IssuedBook books[3];
} LibraryDetails;

typedef struct {
    uint32_t studentProfileOffset;
    uint32_t academicRecordOffset;
    uint32_t hallDetailsOffset;
    uint32_t libraryDetailsOffset;
} StudentFileHeader;




void studentDashboard(const char *student_id, const char *filepath);

#endif