//
// Created by misho on 29/03/19.
//

#include "helper.h"
#include <pthread.h>
#include <stdlib.h>
#include "miner.h"
#include "error_handling.h"
#include <termios.h>
#include <stdio.h>

void init(int count){

    tcgetattr(fileno(stdin), &default_terminal);
    program_terminal = default_terminal;
    program_terminal.c_lflag &=  ~ICANON;
    program_terminal.c_lflag &= ~ECHO;
    program_terminal.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &program_terminal);

    mineral_blocks_count = count;
    map_minerals = mineral_blocks_count * 500;

    xpthread_mutex_init(&global_lock);

    xpthread_mutex_init(&command_lock);


    mineral_blocks = malloc(sizeof(struct mineral) * mineral_blocks_count);
    for(int i = 0; i < mineral_blocks_count; i++){
        mineral_blocks[i].count = 500;
        xpthread_mutex_init(&(mineral_blocks[i].mutex));
    }

    for(int i = 0; i < current_thread_count; i++){
        xpthread_create(&threads[i], mine, (void*)i);

    }


}


void destroy(){
    tcsetattr(fileno(stdin), TCSANOW, &default_terminal);

    for(int i = 0; i < current_thread_count; i++){
        pthread_join(threads[i], NULL);
       // pthread_cancel(threads[i]);
    }
    pthread_mutex_destroy(&global_lock);
    pthread_mutex_destroy(&command_lock);

    for(int i = 0; i < mineral_blocks_count; i++){
        pthread_mutex_destroy(&(mineral_blocks[i].mutex));
    }

    free(mineral_blocks);
}

void xdestroy(){
    for(int i = 0; i < current_thread_count; i++){
        xpthread_join(threads[i]);
    }

    xpthread_mutex_destroy(&global_lock);
    xpthread_mutex_destroy(&command_lock);

    for(int i = 0; i < mineral_blocks_count; i++){
        xpthread_mutex_destroy(&(mineral_blocks[i].mutex));
    }

    free(mineral_blocks);
}

void check_done(){
    if(map_minerals == 0 && warriors >= 20){
        done = true;
    }
}

