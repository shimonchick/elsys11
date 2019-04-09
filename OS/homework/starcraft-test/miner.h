//--------------------------------------------
// NAME: Mihail Kirov
// CLASS: Xib
// NUMBER: 19
// PROBLEM: #1
// FILE NAME: miner.h
// FILE PURPOSE:
// miner thread function
//---------------------------------------------


#ifndef INC_2019_3_26_MINER_H
#define INC_2019_3_26_MINER_H

#include <stdio.h>
#include <pthread.h>
#include "mineral.h"
#include <unistd.h>


extern int mineral_blocks_count;
extern int current_miner_count;
extern int minerals;
extern pthread_mutex_t global_lock;

//--------------------------------------------
// FUNCTION: mine
// Thread function that mines all available mineral blocks and adds the minerals to the total
// PARAMETERS:
// miner_number -> the number of the thread + 1
//----------------------------------------------
void* mine( void* arg);

#endif //INC_2019_3_26_MINER_H
