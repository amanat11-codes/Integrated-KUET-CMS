#include <stdio.h>

struct Course
{
    char courseNo[20];
    char courseTitle[60];
    float credit;
    float gradePoint;
    char letterGrade[5];
};

struct AcademicRecord
{
    int studentId;
    char name[50];
    char session[20];
    char year[20];
    char term[20];

    struct Course courses[8];

    float creditTaken;
    float creditCompleted;
    float termGPA;
    float CGPA;
};


void academicInfoPage(struct AcademicRecord student)
{
    printf("\n");
    printf("                     ACADEMIC RECORDS\n");
    printf("===============================================================\n");

    printf("Student ID : %d\n", student.studentId);
    printf("Name       : %s\n", student.name);
    printf("Session    : %s     Year : %s     Term : %s\n",
           student.session, student.year, student.term);

    printf("---------------------------------------------------------------\n");

    printf("Sl.  Course No.    Course Title                  Credit  GP  Grade\n");
    printf("---------------------------------------------------------------\n");

    for(int i = 0; i < 8; i++)
    {
        printf("%-4d %-13s %-35s %.2f   %.2f  %s\n",
               i + 1,
               student.courses[i].courseNo,
               student.courses[i].courseTitle,
               student.courses[i].credit,
               student.courses[i].gradePoint,
               student.courses[i].letterGrade);
    }

    printf("---------------------------------------------------------------\n");

    printf("Credit Taken           : %.2f\n", student.creditTaken);
    printf("Credit Completed       : %.2f\n", student.creditCompleted);
    printf("Term GPA               : %.2f\n", student.termGPA);
    printf("CGPA                   : %.2f\n", student.CGPA);

    printf("===============================================================\n");
}


int main()
{
    struct AcademicRecord students[2] =
    {
        {
            2107001,
            "Toriqul Islam",
            "2025-2026",
            "First",
            "First",

            {
                {"CSE 1101", "Structured Programming", 3.00, 4.00, "A+"},
                {"CSE 1102", "Structured Programming Lab", 1.50, 3.75, "A"},
                {"CSE 1107", "Discrete Mathematics", 3.00, 3.50, "A-"},
                {"HUM 1107", "English and Human Communication", 3.00, 3.75, "A"},
                {"HUM 1108", "English and Human Comm. Lab", 0.75, 4.00, "A+"},
                {"MATH 1107", "Differential and Integral Calculus", 3.00, 3.50, "A-"},
                {"PHY 1107", "Physics", 3.00, 3.25, "B+"},
                {"PHY 1108", "Physics Laboratory", 1.50, 4.00, "A+"}
            },

            18.75,
            18.75,
            3.60,
            3.60
        },

        {
            2107002,
            "Rahim Ahmed",
            "2025-2026",
            "First",
            "First",

            {
                {"CSE 1101", "Structured Programming", 3.00, 3.50, "A-"},
                {"CSE 1102", "Structured Programming Lab", 1.50, 3.75, "A"},
                {"CSE 1107", "Discrete Mathematics", 3.00, 3.00, "B"},
                {"HUM 1107", "English and Human Communication", 3.00, 3.50, "A-"},
                {"HUM 1108", "English and Human Comm. Lab", 0.75, 4.00, "A+"},
                {"MATH 1107", "Differential and Integral Calculus", 3.00, 3.25, "B+"},
                {"PHY 1107", "Physics", 3.00, 3.50, "A-"},
                {"PHY 1108", "Physics Laboratory", 1.50, 3.75, "A"}
            },

            18.75,
            18.75,
            3.45,
            3.45
        }
    };


    int id;

    printf("Enter Student ID: ");
    scanf("%d", &id);

    for(int i = 0; i < 2; i++)
    {
        if(students[i].studentId == id)
        {
            academicInfoPage(students[i]);
            return 0;
        }
    }

    printf("Student not found.\n");

    return 0;
}