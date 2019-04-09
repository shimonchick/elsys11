//
// Created by misho on 29/03/19.
//

#include "command_center.h"
#include "miner.h"
#include "helper.h"
#include "error_handling.h"
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void train(int sleep_time, bool is_miner, thread_fun_t fun) {
//    struct data arguments = *(struct data *) args;
    sleep(sleep_time);
    bool enough_minerals = true;
    if (pthread_mutex_trylock(&command_lock) == 0) {
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
        current_thread_count++;
        if (is_miner) {
            current_miner_count++;
        }
        xpthread_create(&threads[current_thread_count - 1], fun, (void *) current_miner_count - 1);
    } else {
        printf("Cannot train at this time");
    }


    return;
}