#include "utility.h"
#include <stdio.h>
#include "teacherLoginPage.h"
#include "teacherDashboard.h"

#define TEACHER_ID_MAX_LENGTH 8
#define PASSWORD_MAX_LENGTH 8

void teacherLoginPage(void)
{
    char teacher_id[TEACHER_ID_MAX_LENGTH + 1];
    char password[PASSWORD_MAX_LENGTH + 1];

    while (1)
    {
        clearScreen();
        printBoxedText("TEACHER LOGIN");
        getString("Enter Teacher ID: ", sizeof(teacher_id), teacher_id);
        getString("Enter Password: ", sizeof(password), password);

        FILE *credentialsFile = fopen("database/credentials.dat", "rb");
        if (credentialsFile == NULL)
        {
            getCharacter("Unable to open credentials file. Press ENTER to return...");
            return;
        }

        LoginStatus status = credentialsValidation(
            teacher_id,
            password, TEACHER,
            TEACHER_ID_MAX_LENGTH,
            PASSWORD_MAX_LENGTH,
            credentialsFile);
        fclose(credentialsFile);

        switch (status)
        {
        case SUCCESS:
            getCharacter("Login successful! Press ENTER to continue...");
            teacherDashboard();
            return;
        case INVALID_CREDENTIALS:
            getCharacter("Invalid Teacher ID or Password. Press ENTER to return to login menu...");
            return;
        case RECORD_NOT_FOUND:
            getCharacter("Teacher record not found. Press ENTER to return to login menu...");
            return;
        }
    }
}