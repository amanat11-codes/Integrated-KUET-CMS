#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

const int PADDING = 2;



int getInt(char *prompt)
{
    int value;
    printf("%s", prompt);

    while (scanf("%d", &value) != 1)
    {
        printf("Invalid input. Please enter an integer: ");
        while (getchar() != '\n')
            ; // Clear the input buffer
    }

    while (getchar() != '\n')
        ; // Clear the newline before the next line-based input
    return value;
}

void getString(char *prompt, int maxLength, char *dest)
{
    char buffer[maxLength];
    printf("%s", prompt);
    while (fgets(buffer, maxLength, stdin) == NULL)
    {
        printf("\nInvalid input. Please enter a string: ");
    }

    if (strchr(buffer, '\n') == NULL)
    {
        while (getchar() != '\n' && !feof(stdin))
            ;
    }

    buffer[strcspn(buffer, "\n")] = '\0'; // Remove the newline character
    strncpy(dest, buffer, maxLength - 1);
    dest[maxLength - 1] = '\0'; // Ensure null termination
}

char getCharacter(char *prompt)
{
    printf("%s", prompt);
    char ch;
    scanf("%c", &ch);
    return ch;
}


void printBoxedText(char *text)
{
    int len = strlen(text);
    int lenX = len + 2 * PADDING + 1; // Add padding for the sides

    printf(".");
    for (int i = 0; i < lenX - 1; i++)
    {
        printf("-");
    }
    printf(".\n");
    printf("|");

    for (int i = 0; i < PADDING; i++)
    {
        printf(" ");
    }
    printf("%s", text);
    for (int i = 0; i < PADDING; i++)
    {
        printf(" ");
    }
    printf("|\n");
    printf(".");
    for (int i = 0; i < lenX - 1; i++)
    {
        printf("-");
    }
    printf(".\n");
}

void printUnderlinedText(char *text)
{
    int len = strlen(text) + 2 * PADDING;
    fprintf(stdout, "%s\n", text);
    for (int i = 0; i < len; i++)
    {
        printf("-");
    }
    printf("\n");
}

void printMenuItems(int count, ...)
{
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++)
    {
        char *item = va_arg(args, char *);
        printf("%d. %s\n", i + 1, item);
    }
    va_end(args);
}

LoginStatus credentialsValidation(const char *id, const char *password, UserType usertype, int idMaxLength, int passMaxLength, FILE *credentialsFile)
{
    
    if ((int)strlen(id) != idMaxLength || (int)strlen(password) != passMaxLength)
        return INVALID_CREDENTIALS;

    User user;
    int credentialsMatch = 0;

    rewind(credentialsFile);
    while (fread(&user, sizeof(User), 1, credentialsFile) == 1)
    {
        if (strcmp(user.id, id) == 0 && strcmp(user.pass, password) == 0 && user.type == usertype)
        {
            credentialsMatch = 1;
            break;
        }
    }

    if (!credentialsMatch)
        return INVALID_CREDENTIALS;

    return SUCCESS;
}

void getFilePathForUserType(char *id, UserType userType, char *filepath)
{
    switch (userType)
    {
    case TEACHER:
        snprintf(filepath, 256, "database/teachers/%s.teacher", id);
        break;
    case STUDENT:
        snprintf(filepath, 256, "database/students/%s.student", id);
        break;
    case ADMIN:
        snprintf(filepath, 256, "database/admins/%s.admin", id);
        break;
    default:
        filepath[0] = '\0';
        return;
    }
}

void showDate(Date date, char *dateString)
{
    snprintf(dateString, 11, "%d-%d-%d", date.day, date.month, date.year);
    dateString[10] = '\0';
}



void clearScreen()
{
    system("cls");
}

// function definition here