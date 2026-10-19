#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>

typedef enum
{
    TEACHER = 1,
    STUDENT = 2,
    ADMIN = 3
} UserType;
typedef struct {
    char id[9];
    char pass[9];
    UserType type; // 1 for teacher, 2 for student, 3 for admin
} User;




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
LoginStatus credentialsValidation(const char *id, const char *password, UserType usertype, int idMaxLength, int passMaxLength, FILE *credentialsFile);
void getFilePathForUserType(char *id, UserType userType, char *filepath);
char* showDate(Date date);
void printAppHeader();
//void multiLineBoxedText(int lines, ...);
//int findMaximum(int *lineLengths, int lines);


void clearScreen();



#endif
