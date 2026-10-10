
#include <stdio.h>
#include <windows.h>
#include <string.h>

#include "studentProfilePage.h"
#include "hallDetailsPage.h"
#include "libraryInfoPage.h"
#include "academicInfoPage.h"
#include "teacherProfilePage.h"

static void openHallDetailsWindow(const char *student_id)
{
    char exePath[MAX_PATH];
    char commandLine[MAX_PATH + 300];

    STARTUPINFOA si = {0};
    PROCESS_INFORMATION pi = {0};

    si.cb = sizeof(si);

    DWORD len = GetModuleFileNameA(
        NULL, exePath, MAX_PATH
    );

    if (len == 0 || len >= MAX_PATH)
    {
        printf("Cannot locate the application.\n");
        return;
    }

    snprintf(
        commandLine,
        sizeof(commandLine),
        "\"%s\" --hall-details \"%s\"",
        exePath,
        student_id
    );

    if (!CreateProcessA(
            exePath, commandLine,
            NULL, NULL, FALSE,
            CREATE_NEW_CONSOLE,
            NULL, NULL, &si, &pi))
    {
        printf("Cannot open Hall Details Window. Error: %lu\n",
               GetLastError());
        return;
    }

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
}

void studentDashboard(const char *student_id)
{
    int choice;

    while (1)
    {
        printf("\n\n");
        printf("\t====================================\n");
        printf("\t        KUET STUDENT DASHBOARD\n");
        printf("\t====================================\n");

        printf("\t1. Student Profile\n");
        printf("\t2. Academic Information\n");
        printf("\t3. Hall Details\n");
        printf("\t4. Library Information\n");
        printf("\t5. Teacher Information\n");
        printf("\t6. Logout\n");

        printf("\n\tEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            int ch;

            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }

            printf("\n\tInvalid input! Enter a number.\n");
            continue;
        }

        switch (choice)
        {
            case 1:
                studentProfilePage();
                break;

            case 2:
                academicInfoPage();
                break;

            case 3:
    openHallDetailsWindow(student_id);
    break;

            case 4:
                libraryInfoPage();
                break;

            case 5:
                teacherProfilePage();
                break;

            case 6:
                printf("\n\tLogging out...\n");
                return;

            default:
                printf("\n\tInvalid choice!\n");
        }
    }
}
