#include <stdio.h>
#include "addStudentPage.h"
#include "addTeacherPage.h"
#include "editStudentPage.h"
#include "editTeacherPage.h"
#include "addNoticePage.h"

void adminDashboard()
{
    printf("\tThis is admin dashboard\n");
    addStudent();
    addTeacher();
    editStudent();
    editTeacher();
    addNotice();
}