#include "utility.h"
#include <stdio.h>

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

// function definition here