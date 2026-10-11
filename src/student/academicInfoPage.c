#include <stdio.h>
#include <string.h>
#include "utility.h"

struct Course
{
    char courseNo[20];
    char courseTitle[60];
    float credit;
    float gradePoint;
    char letterGrade[5];
};

static void copyColumnText(char *destination, int size,
                           const char *source)
{
    snprintf(destination, size, "%s", source ? (const char *)source : "");
}

typedef struct
{
    char studentId[20];
    char name[50];
    char session[20];
    char year[20];
    char term[20];
    struct Course courses[5];
    float creditTaken;
    float creditCompleted;
    float termGPA;
    float CGPA;
}AcademicRecord;

void showAcademicRecord(AcademicRecord *record)
{
    printf("\n");
    printBoxedText("ACADEMIC INFORMATION");
    printf("Student ID : %s\n", record->studentId);
    printf("Name       : %s\n", record->name);
    printf("Session    : %s     Year : %s     Term : %s\n",
           record->session, record->year, record->term);

    printf("---------------------------------------------------------------\n");

    printf("Sl.  Course No.    Course Title                  Credit  GP  Grade\n");
    printf("---------------------------------------------------------------\n");

    for (int j = 0; j < 5; j++)
    {
        printf("%-4d %-13s %-35s %.2f   %.2f  %s\n",
               j + 1,
               record->courses[j].courseNo,
               record->courses[j].courseTitle,
               record->courses[j].credit,
               record->courses[j].gradePoint,
               record->courses[j].letterGrade);
    }

    printf("---------------------------------------------------------------\n");

    printf("Credit Taken           : %.2f\n", record->creditTaken);
    printf("Credit Completed       : %.2f\n", record->creditCompleted);
    printf("Term GPA               : %.2f\n", record->termGPA);
    printf("CGPA                   : %.2f\n", record->CGPA);

    printf("===============================================================\n");
    return;
}

void academicInfoPage(sqlite3 *db, char *student_id)
{
    clearScreen();

    const char *sql =
        "SELECT student_id, name, session, year, term, credit_taken, "
        "credit_completed, term_gpa, cgpa, "
        "course1_no, course1_title, course1_credit, course1_grade_point, course1_letter_grade, "
        "course2_no, course2_title, course2_credit, course2_grade_point, course2_letter_grade, "
        "course3_no, course3_title, course3_credit, course3_grade_point, course3_letter_grade, "
        "course4_no, course4_title, course4_credit, course4_grade_point, course4_letter_grade, "
        "course5_no, course5_title, course5_credit, course5_grade_point, course5_letter_grade "
        "FROM academic_information WHERE student_id = ?";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, student_id, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        printf("No academic records found for student ID: %s\n", student_id);
        sqlite3_finalize(stmt);
        getCharacter("Press ENTER to return to the student dashboard...");
        return;
    }
    else
    {
        AcademicRecord record = {0};
        copyColumnText(record.studentId, sizeof(record.studentId),
                       (const char *)sqlite3_column_text(stmt, 0));
        copyColumnText(record.name, sizeof(record.name),
                       (const char *)sqlite3_column_text(stmt, 1));
        copyColumnText(record.session, sizeof(record.session),
                       (const char *)sqlite3_column_text(stmt, 2));
        copyColumnText(record.year, sizeof(record.year),
                       (const char *)sqlite3_column_text(stmt, 3));
        copyColumnText(record.term, sizeof(record.term),
                       (const char *)sqlite3_column_text(stmt, 4));
        record.creditTaken = (float)sqlite3_column_double(stmt, 5);
        record.creditCompleted = (float)sqlite3_column_double(stmt, 6);
        record.termGPA = (float)sqlite3_column_double(stmt, 7);
        record.CGPA = (float)sqlite3_column_double(stmt, 8);

        for (int course = 0; course < 5; course++)
        {
            int column = 9 + course * 5;
            copyColumnText(record.courses[course].courseNo,
                           sizeof(record.courses[course].courseNo),
                           (const char *)sqlite3_column_text(stmt, column));
            copyColumnText(record.courses[course].courseTitle,
                           sizeof(record.courses[course].courseTitle),
                           (const char *)sqlite3_column_text(stmt, column + 1));
            record.courses[course].credit =
                (float)sqlite3_column_double(stmt, column + 2);
            record.courses[course].gradePoint =
                (float)sqlite3_column_double(stmt, column + 3);
            copyColumnText(record.courses[course].letterGrade,
                           sizeof(record.courses[course].letterGrade),
                           (const char *)sqlite3_column_text(stmt, column + 4));
        }

        showAcademicRecord(&record);
    }
    sqlite3_finalize(stmt);
    getCharacter("Press ENTER to return to the student dashboard...");
}