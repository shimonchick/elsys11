//
// Created by misho on 29/03/19.
//

#include "miner.h"
#include "helper.h"
#include "marine.h"
#include "error_handling.h"
#include <stdlib.h>
#include <errno.h>

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define INITIAL_MINER_COUNT 5

void print_mineral_status(int mineral_status[mineral_blocks_count]);

void* mine(void* arg){
    if(current_thread_count > INITIAL_MINER_COUNT) {
        printf("You wanna piece of me, boy?\n");
    }
    int miner_number = (int)arg + 1;

    int minerals_status[mineral_blocks_count];
    for(int i = 0; i < mineral_blocks_count; i++){
        minerals_status[i] = 1; // 1- full, 0 - empty
    }

    while(!are_minerals_empty(minerals_status) && !done){
        for(int mineral_index = 0; mineral_index < mineral_blocks_count; mineral_index++){
            if(minerals_status[mineral_index] == 0){
                continue;
            }
            sleep(3);
            int status;
            if((status = pthread_mutex_trylock(&(mineral_blocks[mineral_index].mutex))) == 0){
                if(mineral_blocks[mineral_index].count <= 0){
                    minerals_status[mineral_index] = 0;
                    xpthread_mutex_unlock(&(mineral_blocks[mineral_index].mutex));
                    continue;
                }
                else{
                    printf("SCV %d is mining from mineral block %d\n", miner_number, mineral_index + 1);
                    int minerals_taken = min(mineral_blocks[mineral_index].count, 8);

                    mineral_blocks[mineral_index].count -= minerals_taken;
                    if(mineral_blocks[mineral_index].count <= 0){
                        minerals_status[mineral_index] = 0;
                    }
                    xpthread_mutex_unlock(&(mineral_blocks[mineral_index].mutex));
                    printf("SCV %d is transporting minerals\n", miner_number);
                    sleep(2);
                    xpthread_mutex_lock(&global_lock);
                    minerals += minerals_taken;
                    map_minerals -= minerals_taken;

                    check_done();

                    xpthread_mutex_unlock(&global_lock);
                    printf("SCV %d delivered minerals to the Command Center\n", miner_number);
                }
            }else if(status == EBUSY){
                continue;
            }
            else{
                perror("pthread_mutex_trylock()");
                exit(1);
            }

        }



    }


    return NULL;
}
//
//void print_mineral_status(int minerals_status[mineral_blocks_count]) {
//    for(int i = 0; i < mineral_blocks_count; i++){
//        printf("Mineral %d status %d ", i, minerals_status[i]);
//    }
//    printf("\n");
//}
