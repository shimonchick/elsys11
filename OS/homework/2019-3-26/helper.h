//--------------------------------------------
// NAME: Mihail Kirov
// CLASS: Xib
// NUMBER: 19
// PROBLEM: #1
// FILE NAME: helper.h
// FILE PURPOSE:
// helper functions to construct and destroy variables used
//---------------------------------------------

#ifndef INC_2019_3_26_HELPER_H
#define INC_2019_3_26_HELPER_H

#include <zconf.h>

extern int mineral_blocks_count;
extern int map_minerals;

struct mineral;
extern struct mineral* mineral_blocks;
extern pthread_mutex_t global_lock;
extern pthread_mutex_t command_lock;
extern pthread_t threads[];
extern pthread_t input_thread;
extern pthread_t training_thread;

extern int current_thread_count;

//--------------------------------------------
// FUNCTION: init
// initializes threads, mutexes and dynamic memory
//----------------------------------------------

void init();


//--------------------------------------------
// FUNCTION: destroy
// Destroys threads, mutexes and dynamic memory
//----------------------------------------------

void destroy();

#endif //INC_2019_3_26_HELPER_H
