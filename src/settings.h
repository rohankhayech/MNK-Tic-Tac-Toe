/*
 * Copyright (c) 2019 Rohan Khayech
 */

#ifndef SETTINGS_H
#define SETTINGS_H

/* Settings struct
|* Holds the m,n,k values used throughout the entire program. 
|* m = width, n = height, k = winning # of tiles */
typedef struct {
    int m;
    int n;
    int k;
} Settings;

#endif