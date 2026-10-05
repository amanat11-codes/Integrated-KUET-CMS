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

    return value;
}

char *getString(char* prompt, int maxLength)
{
    char *buffer = (char *) malloc(maxLength * sizeof(char));
    printf("%s", prompt);
    while (scanf("%s", buffer) != 1){
        printf("Invalid input. Please enter a string: ");
        while (getchar() != '\n'); // Clear the input buffer
    }
    return buffer;
}

void printBoxedText(char* text)
{
    int len = strlen(text);
    int lenX = len + 2 * PADDING + 1; // Add padding for the sides
    int lenY = len + 2 * PADDING; // Add padding for the top and bottom

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


// function definition here