#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "teacherDashboard.h"
#include "studentDashboard.h"

#define TEACHER_COURSE_NAME_LENGTH 12
#define COURSES_DIRECTORY "database/courses/"
#define STUDENTS_DIRECTORY "database/students/"
#define STUDENT_FILEPATH_LENGTH 256
#define CT_MARKS_MIN 0
#define CT_MARKS_MAX 20

static int updateStudentCTMark(const char *studentId, const char *courseName, float ctMarks)
{
    char filepath[STUDENT_FILEPATH_LENGTH];
    StudentFileHeader studentHeader;
    AcademicRecord academicRecord;
    FILE *studentFile;
    long fileSize;
    int courseIndex = -1;

    snprintf(filepath, sizeof(filepath), "%s%.*s.student", STUDENTS_DIRECTORY, 8, studentId);
    studentFile = fopen(filepath, "rb+");
    if (studentFile == NULL)
    {
        fprintf(stderr, "Unable to open student file: %s\n", filepath);
        return 0;
    }

    if (fread(&studentHeader, sizeof(studentHeader), 1, studentFile) != 1 ||
        fseek(studentFile, 0, SEEK_END) != 0 ||
        (fileSize = ftell(studentFile)) < 0 ||
        (unsigned long)studentHeader.academicRecordOffset + sizeof(academicRecord) > (unsigned long)fileSize ||
        fseek(studentFile, (long)studentHeader.academicRecordOffset, SEEK_SET) != 0 ||
        fread(&academicRecord, sizeof(academicRecord), 1, studentFile) != 1)
    {
        fprintf(stderr, "Unable to read the updated-format academic record for student %.*s.\n",
                8, studentId);
        fclose(studentFile);
        return 0;
    }

    for (int i = 0; i < (int)(sizeof(academicRecord.courses) / sizeof(academicRecord.courses[0])); i++)
    {
        if (strncmp(academicRecord.courses[i].courseShortName,
                    courseName, sizeof(academicRecord.courses[i].courseShortName)) == 0)
        {
            courseIndex = i;
            break;
        }
    }

    if (courseIndex < 0)
    {
        fprintf(stderr, "Course %.*s is not present in student %.*s's record.\n",
                TEACHER_COURSE_NAME_LENGTH, courseName, 8, studentId);
        fclose(studentFile);
        return 0;
    }

    academicRecord.courses[courseIndex].ctMarks = ctMarks;

    if (fseek(studentFile, (long)studentHeader.academicRecordOffset, SEEK_SET) != 0 ||
        fwrite(&academicRecord, sizeof(academicRecord), 1, studentFile) != 1 ||
        fflush(studentFile) != 0)
    {
        fprintf(stderr, "Unable to save academic record for student %.*s.\n", 8, studentId);
        fclose(studentFile);
        return 0;
    }

    fclose(studentFile);
    return 1;
}

void updateCTMarks(FILE *teacherFile, TeacherFileHeader *header)
{
    int courseCount = header->taughtCourseCount;
    TaughtCourse *courses;
    int selectedCourse;
    char courseName[TEACHER_COURSE_NAME_LENGTH];
    FILE *courseFile;
    CourseFileHeader courseHeader;
    CourseEnrollment *enrollments;
    char studentId[9];
    int selectedStudent = -1;

    if (courseCount == 0)
    {
        printf("No courses are assigned to this teacher.\n");
        getCharacter("Press ENTER to return to the teacher dashboard...");
        return;
    }

    courses = malloc((size_t)courseCount * sizeof(*courses));
    if (courses == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for course names.\n");
        return;
    }

    if (fseek(teacherFile, (long)header->taughtCoursesOffset, SEEK_SET) != 0 ||
        fread(courses, sizeof(*courses), (size_t)courseCount, teacherFile) != (size_t)courseCount)
    {
        fprintf(stderr, "Unable to read the teacher's course list.\n");
        free(courses);
        return;
    }

    printf("Courses:\n");
    for (int i = 0; i < courseCount; i++)
        printf("%d. %.*s\n", i + 1, TEACHER_COURSE_NAME_LENGTH, courses[i].courseName);

    selectedCourse = getInt("Select a course: ");
    if (selectedCourse < 1 || selectedCourse > courseCount)
    {
        printf("Invalid course selection.\n");
        free(courses);
        getCharacter("Press ENTER to return to the teacher dashboard...");
        return;
    }

    memcpy(courseName, courses[selectedCourse - 1].courseName, sizeof(courseName));

    char coursePath[STUDENT_FILEPATH_LENGTH];
    snprintf(coursePath, sizeof(coursePath), "%s%.*s.course",
             COURSES_DIRECTORY, TEACHER_COURSE_NAME_LENGTH, courseName);
    courseFile = fopen(coursePath, "rb");
    if (courseFile == NULL || fread(&courseHeader, sizeof(courseHeader), 1, courseFile) != 1)
    {
        fprintf(stderr, "Unable to open course roster: %s\n", coursePath);
        if (courseFile != NULL)
            fclose(courseFile);
        free(courses);
        getCharacter("Press ENTER to return to the teacher dashboard...");
        return;
    }

    enrollments = malloc((size_t)courseHeader.studentCount * sizeof(*enrollments));
    if (enrollments == NULL && courseHeader.studentCount > 0)
    {
        fprintf(stderr, "Failed to allocate memory for the course roster.\n");
        fclose(courseFile);
        free(courses);
        getCharacter("Press ENTER to return to the teacher dashboard...");
        return;
    }

    printf("\nStudents enrolled in %.*s:\n", TEACHER_COURSE_NAME_LENGTH, courseName);
    for (uint32_t i = 0; i < courseHeader.studentCount; i++)
    {
        if (fread(&enrollments[i], sizeof(enrollments[i]), 1, courseFile) != 1)
        {
            fprintf(stderr, "Course roster is truncated: %s\n", coursePath);
            fclose(courseFile);
            free(enrollments);
            free(courses);
            getCharacter("Press ENTER to return to the teacher dashboard...");
            return;
        }
        printf("%u. %.*s\n", i + 1, 8, enrollments[i].studentId);
    }

    getString("Enter the student ID to update: ", sizeof(studentId), studentId);
    for (uint32_t i = 0; i < courseHeader.studentCount; i++)
    {
        if (strncmp(enrollments[i].studentId, studentId, sizeof(studentId)) == 0)
        {
            selectedStudent = (int)i;
            break;
        }
    }

    if (selectedStudent < 0)
    {
        printf("That student is not enrolled in this course.\n");
    }
    else
    {
        printf("Enter CT marks (%.0f-%.0f):\n", (float)CT_MARKS_MIN, (float)CT_MARKS_MAX);
        float ctMarks = (float)getInt("> ");
        if (ctMarks < CT_MARKS_MIN || ctMarks > CT_MARKS_MAX)
        {
            printf("CT marks must be between %d and %d.\n", CT_MARKS_MIN, CT_MARKS_MAX);
        }
        else if (updateStudentCTMark(enrollments[selectedStudent].studentId, courseName, ctMarks))
        {
            printf("Updated CT marks for student %.*s.\n", 8, studentId);
        }
    }

    fclose(courseFile);
    free(enrollments);
    free(courses);
    getCharacter("Press ENTER to return to the teacher dashboard...");
}

void updateTermExamMarks(const char *teacherId, const char *filepath)
{
    (void)teacherId;
    (void)filepath;
    printf("Update Term Exam Marks functionality is not implemented yet.\n");
}