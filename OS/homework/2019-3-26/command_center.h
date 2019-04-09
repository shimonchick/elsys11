//
// Created by misho on 29/03/19.
//
//--------------------------------------------
// NAME: Mihail Kirov
// CLASS: Xib
// NUMBER: 19
// PROBLEM: #1
// FILE NAME: command_center.h
// FILE PURPOSE:
// command center thread function and argument data structure
//---------------------------------------------

#ifndef INC_2019_3_26_COMMAND_CENTER_H
#define INC_2019_3_26_COMMAND_CENTER_H

#include <zconf.h>
#include <stdbool.h>

extern int minerals;
extern pthread_mutex_t global_lock;
extern int current_thread_count;
extern pthread_t threads[];

typedef void* (*thread_fun_t)(void*);

void train(int sleep_time, bool is_miner, thread_fun_t fun);

#endif //INC_2019_3_26_COMMAND_CENTER_H
