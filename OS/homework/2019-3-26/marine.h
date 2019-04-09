//--------------------------------------------
// NAME: Mihail Kirov
// CLASS: Xib
// NUMBER: 19
// PROBLEM: #1
// FILE NAME: marine.h
// FILE PURPOSE:
// marine training thread function
//---------------------------------------------


#ifndef INC_2019_3_26_MARINE_H
#define INC_2019_3_26_MARINE_H

#include <zconf.h>
#include <stdbool.h>

extern int warriors;
extern pthread_mutex_t global_lock;
extern int current_miner_count;
extern bool done;
//--------------------------------------------
// FUNCTION: marine
// Thread function that adds a marine and checks for end of game
// PARAMETERS:
// miner_number -> the number of the thread + 1
//----------------------------------------------
void* marine(void* arg);


#endif //INC_2019_3_26_MARINE_H
