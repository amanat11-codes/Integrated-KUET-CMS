#include<stdio.h>
#include <string.h>
#include "utility.h"
#include "adminDashboardPage.h"
#include "adminLoginPage.h"
void adminLoginPage()
{
    while (1)
    {
        clearScreen();

        char ID[8];
        char pass[8];

        printBoxedText("ADMIN LOGIN");
        getString("ID:       ", sizeof(ID), ID);
        getString("Password: ", sizeof(pass), pass);

        if (strcmp(ID, "1001") == 0 && strcmp(pass, "2002") == 0)
            break;
        else
        {        
            getCharacter("\n[ERROR] Invalid ID or password. Press ENTER to return to login page...");
            return;
        }
    }
    
    adminDashboard();

}