#include<stdio.h>
#include "adminDashboardPage.h"
#include "utility.h"
#include <string.h>
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
            char ch;
            ch = getCharacter("Wrong ID or password.\nPress ENTER to try again or any other key to go back... ");

            if (ch != '\n') return;
        }
    }
    
    adminDashboard();

}