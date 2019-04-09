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
#include <stdbool.h>

extern int mineral_blocks_count;
extern int map_minerals;
extern int warriors;
extern bool done;

struct mineral;
extern struct mineral* mineral_blocks;
extern pthread_mutex_t global_lock;
extern pthread_mutex_t command_lock;
extern pthread_t threads[];

extern int current_thread_count;

extern struct termios default_terminal;
extern struct termios program_terminal;

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
//--------------------------------------------
// FUNCTION: xdestroy
// Destroys threads, mutexes and dynamic memory with error checking
//----------------------------------------------

void xdestroy();

//--------------------------------------------
// FUNCTION: check_done
// checks whether the game is done and sets the global done state if needed
//----------------------------------------------
void check_done();

#endif //INC_2019_3_26_HELPER_H
