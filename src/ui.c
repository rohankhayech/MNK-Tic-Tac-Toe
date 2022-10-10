/*
 * Copyright (c) 2019 Rohan Khayech
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "settings.h"
#include "game.h"
#include "fileio.h"
#include "log.h"
#include "ui.h"

int main(int argc, char** argv)
{
    int fail = 0; /* init exit value */
    if (argc != 2) /* print usage info if wrong # of args */
    {
       printf("Usage: ./tictactoe settings\n    where:\n    settings is the filename of the sets file\n"); 
       fail = 1;
    } 
    else 
    {
        /* create the settings and log structs */
        Settings* sets = (Settings*)malloc(sizeof(Settings));
        LinkedList* log = createLog();
        
        /* load in the settings from the file */
        if (loadSettings(argv[1],sets)==0) /* if the file was valid (format wise) */
        {
            menu(sets,log); /* run the menu */
        }
        else
        {
            printf("Invalid settings file, exiting...\n");
            fail = 1;
        }
        
        /* free memory before program exits */
        free(sets);
        sets = NULL;
        freeLog(log);
        log = NULL;
    }
    return fail;
}

void menu(Settings* sets,LinkedList* log) /* runs the main menu until exit is selected */
{
    char input[101];
    int option = -1;
    int loop = 1;
    while (loop == 1)
    {
        printMenu();
        /* get input */
        scanf("%s",input);
        sscanf(input,"%d",&option);
        
        /* select option based on input */
        switch (option)
        {
            case 1:
                runGame(sets, log);
            break;
            case 2:
                viewSettings(sets);
            break;
            case 3:
                displayLog(sets,log);
            break;
            #ifndef SECRET
            case 4:
                saveLog(sets,log);
            break;
            #endif
            case 5:
                loop = 0;
            break;
            #ifdef EDITOR
            case 6:
                editSettings(sets);
            break;
            #endif
            default: /* if an invalid option selected */
                printf("\nPlease select a valid option...\n");
        }
    }
}

void printMenu() /* prints out the menu options */
{
    printf("M-N-K Tic Tac Toe\n");
    printf("    1. Start a new game\n");
    printf("    2. View settings\n");
    printf("    3. View current logs\n");
    #ifndef SECRET
        printf("    4. Save logs to file\n");
    #endif
    #ifdef SECRET
        printf("    4. --Option Unavailable--\n");
    #endif
    printf("    5. Exit\n");
    #ifdef EDITOR
        printf("\n    6. Edit Settings\n");
    #endif
}


void viewSettings(Settings* sets) /* prints out the current settings */
{
    printf("Settings:\n");
    printf("    M: %d\n",sets->m);
    printf("    N: %d\n",sets->n);
    printf("    K: %d\n\n",sets->k);
}

#ifdef EDITOR
void editSettings(Settings* sets) /* if compiled with EDITOR flag, allows user to input new setting values */
{
    int m=-1,n=-1,k=-1;
    int valid = 0;
    int numRead;
    
    char input[101];
    
    printf("\nEdit Settings:\n");
    
    /* input m */
    do
    {
        printf("Enter M (Board Width):\n");
        scanf("%s",input);
        numRead = sscanf(input,"%d",&m);
        if (numRead == 1)
        {
            if (validNum(m) == 1)
            {
                valid = 1;
            }
            else
            {
                printf("Please enter a valid value...");
            }
        }
        else
        {
            printf("Please enter a valid value...");
        }
    } while (valid == 0);
    sets->m = m;
    
    /* input n */
    valid = 0;
    do
    {
        printf("Enter N (Board Height):\n");
        scanf("%s",input);
        numRead = sscanf(input,"%d",&n);
        if (numRead == 1)
        {
            if (validNum(n) == 1)
            {
                valid = 1;
            }
            else
            {
                printf("Please enter a valid value...");
            }
        }
        else
        {
            printf("Please enter a valid value...");
        }
    } while (valid == 0);
    sets->n = n;
    
    /* input k */
    valid = 0;
    do
    {
        printf("Enter K (# in a row to win):\n");
        scanf("%s",input);
        numRead = sscanf(input,"%d",&k);
        if (numRead == 1)
        {
            if ((validNum(k) == 1) && (validK(m,n,k) == 1))
            {
                valid = 1;
            }
            else
            {
                printf("Please enter a valid value...");
            }
        }
        else
        {
            printf("Please enter a valid value...");
        }
    } while (valid == 0);
    sets->k = k;
}
#endif