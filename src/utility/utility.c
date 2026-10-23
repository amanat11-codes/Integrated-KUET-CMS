#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define CREDENTIALS_PATH  "database/credentials.dat"

const int PADDING = 2;

const char *department_short_names[] = {
    "EEE", "CSE", "CE", "ME", "MSE",
    "MTE", "ESE", "ECE", "ARCHI", "URP"};

int getInt(char *prompt)
{
    int value;

    while (1)
    {
        printf("%s", prompt);
        if (scanf("%d", &value) != 1)
        {
            while (getchar() != '\n'); // Clear the input buffer
            printf("[!] Invalid input. Please enter a number.\n");
            continue; // Invalid input, prompt again;
        }
        break;
    }

    return value;
}

void getString(char *prompt, int maxLength, char *dest)
{
    char buffer[maxLength];
    printf("%s", prompt);
    while (fgets(buffer, maxLength, stdin) == NULL)
    {
        if (feof(stdin))
        {
            dest[0] = '\0';
            return;
        }
        printf("[!] Invalid input. Please enter a string: ");
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
    if (scanf("%c", &ch) != 1)
    {
        return '\n';
    }
    if (ch != '\n')
    {
        while (getchar() != '\n' && !feof(stdin))
            ;
    }
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

char *showDate(Date date)
{
    static char dateString[11]; // Buffer to hold the formatted date string
    snprintf(dateString, sizeof(dateString), "%02d-%02d-%04d", date.day, date.month, date.year);
    return dateString;
}

int getTodayDateString(char *dest, size_t destSize)
{
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    if (dest == NULL || destSize < 11 || local == NULL)
        return 0;

    if (strftime(dest, destSize, "%d-%m-%Y", local) == 0)
    {
        dest[0] = '\0';
        return 0;
    }

    return 1;
}

void printAppHeader()
{
    printf("       INTEGRATED KUET CAMPUS MANAGEMENT SYSTEM\n");
    printf("       ========================================\n\n");
}

int validateEmailFormat(const char *email, UserType userType)
{
    (void)userType;

    if (email == NULL || strchr(email, '@') == NULL)
    {
        printf("[!] Invalid email format. Please enter an email containing '@'.\n");
        return 1;
    }

    return 0;
}

int isIdAlreadyRegistered(const char *id)
{
    FILE *cf = fopen(CREDENTIALS_PATH, "rb");
    if (cf == NULL)
        return 0; /* file absent: ID cannot be taken */

    User u;
    while (fread(&u, sizeof(User), 1, cf) == 1)
    {
        if (strcmp(u.id, id) == 0)
        {
            fclose(cf);
            return 1;
        }
    }
    fclose(cf);
    return 0;
}


int isAllDigits(const char *str)
{
    if (str == NULL || str[0] == '\0')
        return 0;
    int i = 0;
    int len = strlen(str);
    while (i < len)
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}
void clearScreen(void)
{
    system("cls");
}

// function definition here
