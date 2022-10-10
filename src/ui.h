/*
 * Copyright (c) 2019 Rohan Khayech
 */

#ifndef UI_H
#define UI_H

void menu(Settings* sets,LinkedList* log);
void printMenu();
void viewSettings(Settings* settings);

#ifdef EDITOR
void editSettings(Settings* sets);
#endif

#endif