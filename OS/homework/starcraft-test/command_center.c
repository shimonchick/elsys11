//
// Created by misho on 29/03/19.
//

#include "command_center.h"
#include "miner.h"
#include "helper.h"
#include "error_handling.h"
#include "marine.h"
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void train(int sleep_time, bool is_miner, thread_fun_t fun) {
    sleep(sleep_time);
    bool enough_minerals = true;
    int status;
    if ((status = pthread_mutex_trylock(&command_lock)) == 0) {
        if (minerals >= 50) {
            minerals -= 50;
        } else {
            enough_minerals = false;
        }
        xpthread_mutex_unlock(&command_lock);

        if (!enough_minerals) {
            printf("Not enough minerals\n");
            return;
        }
        if(is_miner){
            current_thread_count++;
            xpthread_create(&threads[current_thread_count - 1], fun, (void *) current_thread_count - 1);
        
        }
        else{
            marine();
        }
        
    } else  if(status == EBUSY){
        printf("Cannot train at this time\n");
    }
    else{
        perror("pthread_mutex_trylock():");
        exit(1);
    }


    return;
}
