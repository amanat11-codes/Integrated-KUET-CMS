#ifndef UTILITY_H
#define UTILITY_H

typedef enum
{
    TEACHER = 1,
    STUDENT = 2,
    ADMIN = 3
} UserType;

typedef enum
{
    SUCCESS = 0,
    INVALID_CREDENTIALS = 1,
    RECORD_NOT_FOUND = 2,
} LoginStatus;

typedef struct {
    int day;
    int month;
    int year;
} Date; // date in dd-mm-yyyy format

int getInt(char* prompt);
void getString(char* prompt, int maxLength, char* dest);
char getCharacter(char *prompt);
void printBoxedText(char* text);
void printUnderlinedText(char *text);
void printMenuItems(int count, ...);
void clearScreen();
LoginStatus credentialsValidation(char *id, const char *password, int idMaxLength, int passMaxLength, UserType userType);
void getFilePathForUserType(char *id, UserType userType, char *filepath);
void showDate(Date date, char *dateString);


#endif
