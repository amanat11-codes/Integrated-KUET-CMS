#include <stdio.h>
#include "loginPage.h"
#include "studentLoginPage.h"
#include "teacherLoginPage.h"
#include "adminLoginPage.h"
#include "noticesPage.h"
void showStudentLoginPage()
{
    studentLoginPage();
}
void showTeacherLoginPage()
{
    teacherLoginPage();
}
void showAdminLoginPage()
{
    adminLoginPage();
}
void showNoticesPage()
{
    printf("This is notices page\n");

}

int main(void)
{
    showStudentLoginPage();
    showTeacherLoginPage();
    showAdminLoginPage();
    showNoticesPage();
    return 0;
}