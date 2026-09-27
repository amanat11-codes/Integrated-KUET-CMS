#include<stdio.h>
#include "ctMarksPage.h"
#include "termExamMarksPage.h"
#include "checkStudentProfilePage.h"


void teacherDashboard()
{
    printf("\tThis is teacher dashboard\n");
    updateCTMarks();
    updateTermMarks();
    checkStudentProfile();
}