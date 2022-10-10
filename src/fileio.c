/* Parts of this file adapted from code previously submitted for UCP Prac 6 Sem 2 2019 - Rohan Khayech*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "settings.h"
#include "log.h" /* includes LinkedList.h */
#include "fileio.h"

/*Basic File I/O structure adapted from code previously submitted for UCP Prac 6 Sem 2 2019 - Rohan Khayech*/
int loadSettings(char* filename, Settings* settings) /* loads in the settings for the game from the specified files */
{
    char line[6]; /*two chars for m=, three for the number (just in case) and one for \n*/
    char setting;
    int fail = 0, num;
    int m=-1, n=-1, k=-1;
    FILE* file = fopen(filename, "rb");
    
    if(file == NULL) {
        perror("Error opening file.");
        fail = 1;
    }
    else /*if file opens*/
    {
        /* read each line until the end is reached */
        while(!feof(file)&&fail==0) 
        {
            if (fgets(line,6,file) != NULL) { /*read the line and check if it worked */
                int numRead = sscanf(line, "%c=%d", &setting,&num); /* read the setting and the num */
                if (numRead != 2)
                {
                   fail=1; /*invalid format*/   
                }
                else
                {
                    strUpper(&setting); /*account for both upper and lowercase setting chars*/
                    switch (setting)
                    {
                        case 'M':
                            if (m == -1)
                            {
                                m = num; /*set the width if it hasn't been set before */
                            }
                            else
                            {
                                fail = 1; /* duplicate setting */
                            }
                        break;
                        case 'N':
                            if (n == -1)
                            {
                                n = num; /*set the height if it hasn't been set before */
                            }
                            else
                            {
                                fail = 1; /* duplicate setting */
                            }
                        break;
                        case 'K':
                            if (k == -1)
                            {
                                k = num; /*set the k value if it hasn't been set before */
                            }
                            else
                            {
                                fail = 1; /* duplicate setting */
                            }
                        break;
                        default:
                            fail = 1; /*not a valid setting*/
                    }
                }
            }
            else
            {
                fail = 1;  /*error or end of file*/
            } 
        }
        
        /*Check settings*/
        if ( (validNum(m)==0) || (validNum(n)==0) || (validNum(k)==0) || (validK(m,n,k)==0))
        {
            fail = 1;
        } else {
            settings->m = m;
            settings->n = n;
            settings->k = k;
        }
        
        if(ferror(file)||fail==1) 
        {
            perror("Error reading file.\n");
        }
        fclose(file);
    }
    return fail;
}
/* End self-adapted code */
int validNum(int num) /* checks the number is valid */
{
    int valid = 0;
    if ((num>=3) && (num<95))
    {
       valid = 1; 
    }
    return valid;
}

int validK(int m, int n, int k) /* checks if k is valid (fits on the board) */
{
    int valid = 0;
    if ((k<=m) || (k<=n))
    {
       valid = 1;
    }
    return valid;
}

/*Function previously submitted for UCP Prac 4 Sem 2 2019 - Rohan Khayech*/
void strUpper(char* str) /* converts any lowercase chars in the string to uppercase */
{
    int i;
    for (i=0; i<strlen(str); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 'a'-'A';
        }
    }
}
/* End self-referenced function */

/*Basic File I/O structure adapted from code previously submitted for UCP Prac 6 Sem 2 2019 - Rohan Khayech*/
void saveLog(Settings* sets, LinkedList* log) /*saves the log to the file */
{
    FILE* file;
    
    /* init the filename */
    char filename[30];
    int hour, min, day, month;
    
    getTimestamp(&hour,&min,&day,&month);
    /*build the filename */
    sprintf(filename,"MNK_%d-%d-%d_%02d-%02d_%02d-%02d.log",sets->m,sets->n,sets->k,hour,min,day,month);
    
    /*open the file */
    file = fopen(filename, "wb");
    if(file == NULL) {
        perror("Error opening files.");
    }
    else /* if the file opens */
    {
        /* write the settings */
        fprintf(file,"Settings:\n");
        fprintf(file,"    M: %d\n",sets->m);
        fprintf(file,"    N: %d\n",sets->n);
        fprintf(file,"    K: %d\n\n",sets->k);
        
        /* write the log */
        printLinkedListToFile(log,&saveGameEntry,file);
        
        if(ferror(file)) {
            perror("Error writing to ");
            printf("'%s'\n",filename);
        } 
        else
        {
            printf("Saved logs to '%s'\n",filename);
        }

        fclose(file);
     }      
}
/* End self-adapted code */

void saveGameEntry(void* value, FILE* file) /* passed to printLinkedListToFile to write each game entry */
{
    GameEntry* gameLog = value;
    fprintf(file,"Game %d:\n",gameLog->game);
    printLinkedListToFile(gameLog->turns,&saveTurnEntry,file);
}

void saveTurnEntry(void* value, FILE* file) /* passed to printLinkedListToFile to write each turn entry */
{
    TurnEntry* turnLog = value;
    fprintf(file,"    Turn: %d\n",turnLog->turn);
    fprintf(file,"    Player: %c\n",turnLog->player);
    fprintf(file,"    Location: %d,%d\n\n",turnLog->space->x,turnLog->space->y);
}

void getTimestamp(int* hour, int* min, int* day, int* month) /* returns date/time info */
{
    /* Adapted from code from Techie Delight (provided in the assignment spec),
     * https://www.techiedelight.com/print-current-date-and-time-in-c/
     * (Accessed 13/10/2019) */
    struct tm* local;
    
    /* Get local time */
    time_t now;
    time(&now);
    
    local = localtime(&now);
    
    /* Split into individual values */
    *hour = local->tm_hour;
    *min = local->tm_min;
    *day = local->tm_mday;
    *month = local->tm_mon+1;
    
    /* End of code adapted from Techie Delight */
}