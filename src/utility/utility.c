#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int PADDING = 2;

int getInt(char* prompt)
{
    int value;
    printf("%s", prompt);

    while (scanf("%d", &value) != 1){
        printf("Invalid input. Please enter an integer: ");
        while (getchar() != '\n'); // Clear the input buffer
    }

    while (getchar() != '\n'); // Clear the newline before the next line-based input
    return value;
}

void getString(char* prompt, int maxLength, char* dest)
{
    char buffer[maxLength];
    printf("%s", prompt);
    while (fgets(buffer, maxLength, stdin) == NULL){
        printf("\nInvalid input. Please enter a string: ");
    }

    if (strchr(buffer, '\n') == NULL) {
        while (getchar() != '\n' && !feof(stdin));
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

void printBoxedText(char* text)
{
    int len = strlen(text);
    int lenX = len + 2 * PADDING + 1; // Add padding for the sides

    printf(".");
    for (int i = 0; i < lenX - 1; i++){
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
    for (int i = 0; i < lenX - 1; i++){
        printf("-");
    }
    printf(".\n");
}

void printUnderlinedText(char *text)
{
    int len = strlen(text) + 2 * PADDING;
    printf("%s\n", text);
    for (int i = 0; i < len; i++)
    {
        printf("-");
    }
    printf("\n");
}


void clearScreen()
{
    system("cls");
}

// function definition here