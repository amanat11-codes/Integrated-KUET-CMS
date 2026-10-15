#include "utility.h"
#include <stdio.h>
#include <windows.h>
#include <stdio.h>
#include "studentLoginPage.h"
#include "studentDashboard.h"

#define STUDENT_ID_MAX_LENGTH 8 // excluding null terminator
#define PASSWORD_MAX_LENGTH 8   // excluding null terminator

void studentLoginPage(void)
{
    char student_id[STUDENT_ID_MAX_LENGTH + 1]; // +1 for null terminator
    char password[PASSWORD_MAX_LENGTH + 1];

    while (1)
    {
        clearScreen();
        printBoxedText("STUDENT LOGIN");
        getString("Enter Student ID: ", sizeof(student_id), student_id);
        getString("Enter Password: ", sizeof(password), password);

        FILE *credentialsFile = fopen("database/credentials.dat", "rb");
        if (credentialsFile == NULL)
        {
            getCharacter("Unable to open credentials file. Press ENTER to return...");
            return;
        }

        LoginStatus status = credentialsValidation(
            student_id,
            password, STUDENT,
            STUDENT_ID_MAX_LENGTH,
            PASSWORD_MAX_LENGTH,
            credentialsFile);
        fclose(credentialsFile);

        switch (status)
        {
        case SUCCESS:
            getCharacter("Login successful! Press ENTER to continue...");
            char filepath[256];
            getFilePathForUserType(student_id, STUDENT, filepath);
            studentDashboard(student_id, filepath);
            return;
        case INVALID_CREDENTIALS:
            getCharacter("Invalid Student ID or Password.");
            return;
        case RECORD_NOT_FOUND:
            getCharacter("Student record not found.");
            return;
        }
    }
}
