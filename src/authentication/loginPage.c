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
    noticesPage();
}

void loginPage(void)
{
    int choice;

    printf("1. Student Login\n");
    printf("2. Teacher Login\n");
    printf("3. Admin Login\n");
    printf("4. Show Notices\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            showStudentLoginPage();
            break;

        case 2:
            showTeacherLoginPage();
            break;

        case 3:
            showAdminLoginPage();
            break;

        case 4:
            showNoticesPage();
            break;

        default:
            printf("Invalid choice!\n");
    }
}