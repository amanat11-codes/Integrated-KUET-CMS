#include <stdio.h>
#include "loginPage.h"
#include "studentLoginPage.h"
void showStudentLoginPage()
{
    studentLoginPage();
}
void showTeacherLoginPage()
{
    printf("This is teacher login page\n");

}
void showAdminLoginPage()
{
    printf("This is admin login page\n");

}
void showNoticesPage()
{
    printf("This is notices page\n");

}

int main(void)
{
    showStudentLoginPage();
    return 0;
}