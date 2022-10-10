#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "settings.h"
#include "log.h" /*includes LinkedList.h*/
#include "ui.h"

LinkedList* createLog() /* creates the log list */
{
    LinkedList* log = createLinkedList();
    
    return log;
}

GameEntry* addGameEntry(LinkedList* log) /*creates a new game entry and adds it to the log */
{
    static int gameCount = 1; /*tracks how many game entries have been created*/
    
    /* create game entry */
    GameEntry* entry = (GameEntry*)malloc(sizeof(GameEntry));
    entry->game = gameCount;
    entry->turns = createLinkedList();
    
    /* insert it to the log */
    insertLast(log, entry);
    
    gameCount++;

    return entry;
}

void addTurnEntry(GameEntry* game,int turn,char player,int x, int y) /*creates a new turn entry and adds it to the log */
{
    TurnEntry* entry;
    
    /* create the location */
    Location* space = (Location*)malloc(sizeof(Location));
    space->x = x;
    space->y = y;
    
    /* create the turn entry */
    entry = (TurnEntry*)malloc(sizeof(TurnEntry));
    entry->turn = turn;
    entry->player = player;
    entry->space = space;
    
    /* add it to the game entry */
    insertLast(game->turns, entry);
}

void displayLog(Settings* sets, LinkedList* log) /* displays the current logs to the terminal */
{
    viewSettings(sets);
    
    printLinkedList(log,&displayGameEntry);
}

void displayGameEntry(void* value) /* passed to printLinkedList to print each game entry */
{
    GameEntry* gameLog = value;
    printf("Game %d:\n",gameLog->game);
    printLinkedList(gameLog->turns,&displayTurnEntry);
}

void displayTurnEntry(void* value) /* passed to printLinkedList to print each turn entry */
{
    TurnEntry* turnLog = value;
    printf("    Turn: %d\n",turnLog->turn);
    printf("    Player: %c\n",turnLog->player);
    printf("    Location: %d,%d\n\n",turnLog->space->x,turnLog->space->y);
    
}

void freeLog(LinkedList* log) /* frees the log */
{
    freeLinkedList(log,&freeGameEntry);
}

void freeGameEntry(void* value) /* passed to freeLinkedList to free each game entry */
{
    GameEntry* gameLog = value;
    freeLinkedList(gameLog->turns,&freeTurnEntry);
    free(gameLog);
}

void freeTurnEntry(void* value)  /* passed to freeLinkedList to free each turn entry */
{
    TurnEntry* turnLog = value;
    free(turnLog->space);
    free(turnLog);
}