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
// adds a marine and checks for end of game
// PARAMETERS:
//----------------------------------------------
void marine();


#endif //INC_2019_3_26_MARINE_H
