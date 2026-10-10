#ifndef UTILITY_H
#define UTILITY_H

#include "sqlite3.h"

int getInt(char* prompt);
void getString(char* prompt, int maxLength, char* dest);
char getCharacter(char *prompt);
int getTableRows(sqlite3 *db, const char *tableName);
void printBoxedText(char* text);
void printUnderlinedText(char *text);
void clearScreen();

// function prototype

#endif
