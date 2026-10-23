#include <stdio.h>
#include <string.h>
#include <io.h>
#include "removeAccountPage.h"
#include "utility.h"

#define TEACHERS_DIR "database/teachers/"
#define STUDENTS_DIR "database/students/"
#define CREDENTIALS_PATH "database/credentials.dat"

static int removeCredential(const char *id, UserType userType)
{
    FILE *credentialsFile = fopen(CREDENTIALS_PATH, "rb+");
    if (credentialsFile == NULL)
        return -1;

    User user;
    long recordOffset;
    long writeOffset = -1;
    int found = 0;

    while ((recordOffset = ftell(credentialsFile)) >= 0 &&
           fread(&user, sizeof(user), 1, credentialsFile) == 1)
    {
        if (!found && user.type == userType && strcmp(user.id, id) == 0)
        {
            found = 1;
            writeOffset = recordOffset;
            continue;
        }

        if (found)
        {
            long nextReadOffset = ftell(credentialsFile);

            if (fseek(credentialsFile, writeOffset, SEEK_SET) != 0 ||
                fwrite(&user, sizeof(user), 1, credentialsFile) != 1 ||
                fseek(credentialsFile, nextReadOffset, SEEK_SET) != 0)
            {
                fclose(credentialsFile);
                return -1;
            }

            writeOffset += (long)sizeof(user);
        }
    }

    if (!found)
    {
        fclose(credentialsFile);
        return 0;
    }

    if (fflush(credentialsFile) != 0 ||
        _chsize(_fileno(credentialsFile), writeOffset) != 0 ||
        fclose(credentialsFile) != 0)
        return -1;

    return 1;
}

void removeAccountPage(UserType User)
{
    clearScreen();
    char id[9]; // Assuming IDs are 8 characters long + null terminator
    char filepath[256];
    char prompt[] = "[?] Are you sure you want to remove this account? (Y/N): ";
    char ch;
    switch (User)
    {
    case TEACHER: {
        getString("[?] Enter Teacher ID to remove: ", 9, id);
        ch = getCharacter(prompt);
        if (ch != 'Y' && ch != 'y')
        {
            printf("Operation cancelled. Teacher account with ID %s was not removed.\n", id);
            getCharacter("[?] Press ENTER to go back...\n");
            return;
        }
        snprintf(filepath, sizeof(filepath), "%s%s.teacher", TEACHERS_DIR, id);
        int credentialResult = removeCredential(id, TEACHER);
        if (credentialResult == 1 && remove(filepath) == 0)
        {
            printf("Teacher account with ID %s has been removed successfully.\n", id);
        }
        else if (credentialResult == 0)
            printf("[!] Error: No teacher credentials found for ID %s.\n", id);
        else
            printf("[!] Error: Could not remove teacher account with ID %s completely.\n", id);

        getCharacter("[?] Press ENTER to go back...\n");
        return;
    }

    case STUDENT: {
        getString("[?] Enter Student ID to remove: ", 9, id);
        ch = getCharacter(prompt);
        if (ch != 'Y' && ch != 'y')
        {
            printf("Operation cancelled. Student account with ID %s was not removed.\n", id);
            getCharacter("[?] Press ENTER to go back...\n");
            return;
    }
        }
        snprintf(filepath, sizeof(filepath), "%s%s.student", STUDENTS_DIR, id);
        int credentialResult = removeCredential(id, STUDENT);
        if (credentialResult == 1 && remove(filepath) == 0)
            printf("Student account with ID %s has been removed successfully.\n", id);
        else if (credentialResult == 0)
            printf("[!] Error: No student credentials found for ID %s.\n", id);
        else
            printf("[!] Error: Could not remove student account with ID %s completely.\n", id);

        getCharacter("[?] Press ENTER to go back...\n");
        return;

    case ADMIN:
        printf("Admin account removal is not allowed.\n");
        getCharacter("[?] Press ENTER to go back...\n");
        return;
    }
}
