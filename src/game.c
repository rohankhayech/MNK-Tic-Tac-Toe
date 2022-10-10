#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "settings.h"
#include "game.h" /* includes log.h and LinkedList.h */

void runGame(Settings* sets,LinkedList* log) /* initilises the game and starts turns until the game ends */
{
    /* initilise game */
    char** board;
    int turn;
    char player, winner;
    GameEntry* gameLog;
    startGame(sets,&board,&turn,&player,&winner,log,&gameLog);
    printBoard(sets,board);
    
    /* Take turns, print the board and check for winner */
    while (winner == 'n') { /* while no winner */
        takeTurn(sets,board,&player,&turn,gameLog);
        printBoard(sets,board);
        checkBoard(sets,board,&winner);
    }
    
    /* end game */
    announceWinner(winner);
    freeBoard(sets,board);
    board = NULL;
}

void startGame(Settings* sets,char*** board,int* turn,char* player,char* winner,LinkedList* log,GameEntry** gameLog) /* initilises the game an the board */
{
    int i,j;
    
    /* init game */
    *turn = 1;
    *player = 'X'; /*no winner*/
    *winner = 'n';
    
    /* init board */
    /* rows */
    *board = (char**)calloc(sets->n,sizeof(char*));
    
    /* cols */
    for(j=0;j<sets->n;j++)
    {
        (*board)[j] = (char*)calloc(sets->m,sizeof(char)); 
        for (i=0; i<sets->m;i++)
        {
            (*board)[j][i] = ' ';
        }
    }
    
    /* init log entry */
    *gameLog = addGameEntry(log); 
}

void printBoard(Settings* sets, char** board) /* prints the board to the terminal */
{
    
    int i,j;
    
    /* system("clear"); */ /* can print to existing board if used */
    
    /*print top border */
    for (i=0; i<sets->m;i++)
    {
        printf("====");
    }
    printf("=\n");
    /* print each row with borders */
    for(j=0;j<sets->n;j++)
    {
        printf("|");
        for (i=0; i<sets->m;i++)
        {
            printf(" %c |",board[j][i]);
        }
        printf("\n=");
        for (i=0; i<sets->m;i++)
        {
            printf("====");
        }
        printf("\n");
    }
}

void freeBoard(Settings* sets, char** board) /* frees the board array */
{
    int j;
    for(j=0;j<sets->n;j++)
    {
        free(board[j]);
    }
    free(board);
}

void takeTurn(Settings* sets, char** board,char* player,int* turn, GameEntry* gameLog) /* takes input and places a move */
{
    int x,y;
    int valid = 0;
    int numRead;
    char input[101];
    printf("%c's Turn:\n",*player);
    printf("Pick a space by entering \"x,y\"\n");
    
    /* get input */
    do
    {
        scanf("%s",input);
        numRead = sscanf(input,"%d,%d",&x,&y);
        if (numRead == 2) 
        {
            valid = validMove(sets,board,x,y);
        }
        
        if (valid == 0)
        {
            printf("Invalid move, try again...\n");
        }
    } while (valid==0);
    
    /* place move */
    board[y-1][x-1] = *player;
    
    /* enter turn entry */
    addTurnEntry(gameLog,*turn,*player,x,y);
    
    /* switch player */
    if (*player == 'X')
    {
        *player = 'O';
    } 
    else
    {
        *player = 'X';
    }
    
    /* increase turn */
    (*turn)++;
}

int validMove(Settings* sets, char** board, int x, int y) /* checks if a move can be placed at the specified coordinates */
{
    int valid = 0;
    if ((x>0)&&(x<=sets->m)&&(y>0)&&(y<=sets->n)) /* if the coordinates are on the board */
    {
        if (board[y-1][x-1]==' ') /* if the space is empty */
        {
            valid = 1;
        }
    }
    return valid;
}

void checkBoard(Settings* sets, char** board,char* winner) /* checks the board for a winner */
{
    checkHorizontal(sets,board,winner);
    checkVertical(sets,board,winner);
    checkDiagonals(sets,board,winner);
    checkDraw(sets,board,winner);
}

void checkHorizontal(Settings* sets, char** board,char* winner) /* checks for a horizontal winning sequence */
{
    int j,i;
    for (j=0; j<sets->n; j++) /* for every row */ 
    {
        int adjCount = 1;
        char prev = board[j][0];
        for (i=1; i<sets->m; i++) /* for every col */ 
        {
            if ((board[j][i]==prev)&&!(board[j][i]==' ')) 
            {
                adjCount++; /* if the current space is the same as the prev space, increase the adjacent count*/
            } 
            else 
            {
                adjCount = 1; /*otherwise reset adjacent count to 1*/
            }
            /*printf("Space (%d,%d): %c, Prev: %c, Num: %d | ",j,i,board[j][i],prev,adjCount);*/
            prev = board[j][i];
            
            
            if (adjCount == sets->k) 
            {
                *winner = board[j][i]; /*if the winning numbers of tiles in a row is reached, set the winner*/
            }
        }
    }
}

void checkVertical(Settings* sets, char** board,char* winner) /* checks for a vertical winning sequence */
{
    int i,j;
    for (i=0; i<sets->m; i++) /* for every col */ 
    {
        int adjCount = 1;
        char prev = board[0][i];
        for (j=1; j<sets->n; j++) /* for every row */ 
        {
            if ((board[j][i]==prev)&&!(board[j][i]==' ')) 
            {
                adjCount++; /* if the current space is the same as the prev space, increase the adjacent count*/
            } 
            else 
            {
                adjCount = 1; /*otherwise reset adjacent count to 1*/
            }
            prev = board[j][i];
            
            
            if (adjCount == sets->k) 
            {
                *winner = board[j][i]; /*if the winning numbers of tiles in a row is reached, set the winner*/
            }
        }
    }
}

void checkDiagonals(Settings* sets, char** board,char* winner) /* checks for a vertical winning sequence */
{
    int j,i;
    
    
    for (j=0; j<(sets->n-(sets->k-1)); j++) /* for every row that can start a k diagonal that fits on the board*/
    { 
        
        /* TL to BR diagonals */
        for (i=0; i<(sets->m-(sets->k-1)); i++) /*for every space in that row that can start a k diagonal that fits on the board */
        { 
            int adjCount = 1;
            char prev = board[j][i];
            int l=1;
            while ((l<sets->k)&&(board[j+l][i+l]==prev)&&!(board[j+l][i+l]==' ')) 
            /* keep checking the next diagonal space until a different move or empty space is found */
            {
                adjCount++;
                prev = board[j+l][i+l];
                l++;
            }
            if (adjCount == sets->k) 
            {
                *winner = board[j][i];  /*if the winning numbers of tiles in a row is reached, set the winner*/
            }
        }
        
        /* TR to BL diagonals */
        for (i=sets->m-1; i>=(sets->k-1); i--) /*for every space in that row that can start a k diagonal that fits on the board */
        { 
            int adjCount = 1;
            char prev = board[j][i];
            int l=1;
            while ((l<sets->k)&&(board[j+l][i-l]==prev)&&!(board[j+l][i-l]==' '))
            /* keep checking the next diagonal space until a different move or empty space is found */                
            {
                adjCount++;
                prev = board[j+l][i-l];
                l++;
            }
            if (adjCount == sets->k) 
            {
                *winner = board[j][i];  /*if the winning numbers of tiles in a row is reached, set the winner*/
            }
        }
    }
}

void checkDraw(Settings* sets, char** board,char* winner) /* checks if there are no more spaces left */
{
    int j=0,i=0;
    int spacesLeft = 0;
    /* check every space on the board until a free space is found */
    while (j<sets->n&&spacesLeft==0) 
    {
        i = 0;
        while (i<sets->m&&spacesLeft==0)
        {
            if (board[j][i] == ' ')
            {
                spacesLeft = 1;
            }
            i++;
        }
        j++;
    }
    if (spacesLeft == 0) /* if no free spaces left declare a draw */
    {
        *winner = 'd';
    }
}

void announceWinner(char winner) /* prints the winner or draw */
{
    if (winner == 'd') /* draw */
    {
        printf("Game drawn.\n\n");
    }
    else
    {
        printf("%c wins!\n\n",winner);
    }
}