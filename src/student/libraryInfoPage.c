#include <stdio.h>

void libraryInfoPage()
{
    int choice;

    printf("\n\t\t===== LIBRARY INFORMATION =====\n");

    printf("\n\tStudent Name : Toriqul Islam\n");

    printf("\n\tBooks Borrowed:\n");
    printf("\t1. Let Us C\n");
    printf("\t2. Discrete Mathematics\n");

    printf("\n\tIssue Date:\n");
    printf("\t1. 01-10-2026\n");
    printf("\t2. 03-10-2026\n");

    printf("\n\tReturn Date:\n");
    printf("\t1. 15-10-2026\n");
    printf("\t2. 17-10-2026\n");

    printf("\n\t================================\n");
}

int main()
{
    libraryInfoPage();

    return 0;
}