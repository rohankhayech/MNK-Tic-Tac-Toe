#ifndef GAME_H
#define GAME_H

#include "log.h" /* includes LinkedList.c */

void runGame(Settings* sets,LinkedList* log);
void startGame(Settings* sets,char*** board,int* turn,char* player,char* winner,LinkedList* log,GameEntry** gameLog);
void printBoard(Settings* sets, char** board);
void freeBoard(Settings* sets, char** board);
void takeTurn(Settings* sets, char** board,char* player,int* turn, GameEntry* gameLog);
int validMove(Settings* sets, char** board, int x, int y);
void checkBoard(Settings* sets, char** board,char* winner);
void checkHorizontal(Settings* sets, char** board,char* winner);
void checkVertical(Settings* sets, char** board,char* winner);
void checkDiagonals(Settings* sets, char** board,char* winner);
void checkDraw(Settings* sets, char** board,char* winner);
void announceWinner(char winner);

#endif