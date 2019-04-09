#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <termios.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

#include "helper.h"
#include "miner.h"
#include "command_center.h"
#include "marine.h"

#include "error_handling.h"

//--------------------------------------------
// NAME: Mihail Kirov
// CLASS: Xib
// NUMBER: 19
// PROBLEM: #1
// FILE NAME: main.c
// FILE PURPOSE:
// starcraft 3 prototype
//---------------------------------------------
#define MAX_THREAD_COUNT 200
#define INITIAL_MINER_COUNT 5


pthread_t threads[MAX_THREAD_COUNT];


int warriors = 0;
int mineral_blocks_count = 2;

int minerals = 0;
int map_minerals;

int current_thread_count = INITIAL_MINER_COUNT;
int current_miner_count = INITIAL_MINER_COUNT;
pthread_mutex_t global_lock;
pthread_mutex_t command_lock;


//global game state. It can be set from different functions/ different files
bool done = false;

struct termios default_terminal;
struct termios program_terminal;



//--------------------------------------------
// FUNCTION: input
// Thread function that reads user input and creates the training thread
//
//----------------------------------------------

void input(){
    char command;
    //fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
    
    while (!done) {
        //int num_read = read(0, &command, 1);
        //if(num_read == 0){
        //    continue;
        //}
        command = getc(stdin);    
        switch (command) {
            case 's':;
                train(4, true, mine);
                break;
            case 'm':;
                train(1, false, NULL);
                break;
            case 'q':
                done = true;
                break;

        }
    }
    return;
}
//--------------------------------------------
// FUNCTION: main
// creates the input thead and calls all the other worker functions
// PARAMETERS:
// argc -> argument count
// argv -> argument vector. Add a parameter to change the number of minerals in the game
//----------------------------------------------

int main(int argc, char *argv[]) {

    int mineral_count = 2;
    if (argc == 2) {
        mineral_count = atoi(argv[1]);
    }
    init(mineral_count);
    
    input();
    
//    destroy();
    xdestroy();
    printf("Map minerals %d, player minerals %d, SCVs %d, Marines %d\n", mineral_count * 500, minerals,
            current_thread_count, warriors);
    exit(0);
}
