/*
 * Copyright (c) 2019 Rohan Khayech
 */

#ifndef LOG_H
#define LOG_H

#include "LinkedList.h"

/* Location struct
|* Holds an x,y board coordinate used in the turn log entries */
typedef struct {
    int x;
    int y;
} Location;

/* TurnEntry struct
|* Holds the number, player responsible and board space of each turn in a game.
|* Used to store turns in the log for viewing and saving */
typedef struct {
    int turn;
    char player;
    Location* space;
} TurnEntry;


/* GameEntry struct
|* Holds the number, and the list of turns for each game.
|* Used to store games in the log for viewing and saving */
typedef struct {
    int game;
    LinkedList* turns;
} GameEntry;


LinkedList* createLog();
GameEntry* addGameEntry(LinkedList* log);
void addTurnEntry(GameEntry* game,int turn,char player,int x, int y);
void displayLog(Settings* sets, LinkedList* log);
void displayGameEntry(void* value);
void displayTurnEntry(void* value);
void freeLog(LinkedList* log);
void freeGameEntry(void* value);
void freeTurnEntry(void* value);

#endif