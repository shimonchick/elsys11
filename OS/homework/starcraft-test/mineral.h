//--------------------------------------------
// NAME: Mihail Kirov
// CLASS: Xib
// NUMBER: 19
// PROBLEM: #1
// FILE NAME: mineral.h
// FILE PURPOSE:
// mineral helper functions and structures
//---------------------------------------------

#ifndef INC_2019_3_26_MINERAL_H
#define INC_2019_3_26_MINERAL_H

#include <pthread.h>

struct mineral{
    pthread_mutex_t mutex;
    int count;
};

struct mineral* mineral_blocks;


extern int mineral_blocks_count;

//--------------------------------------------
// FUNCTION: are_minerals_empty
// checks the local mineral status of a miner returns whether or not they are empty
// PARAMETERS:
// mineral_status --> the local mineral status of each miner
//----------------------------------------------
int are_minerals_empty(int mineral_status[mineral_blocks_count]);

#endif //INC_2019_3_26_MINERAL_H
