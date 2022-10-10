#ifndef FILE_H
#define FILE_H

int loadSettings(char* filename, Settings* settings);
int validNum(int num);
int validK(int m, int n, int k);
void strUpper(char* str);
void saveLog(Settings* sets, LinkedList* log);
void saveGameEntry(void* value, FILE* file);
void saveTurnEntry(void* value, FILE* file);
void getTimestamp(int* hour, int* min, int* day, int* month);

#endif