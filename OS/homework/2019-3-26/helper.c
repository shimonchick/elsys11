//
// Created by misho on 29/03/19.
//

#include "helper.h"
#include <pthread.h>
#include <stdlib.h>
#include "miner.h"
#include "error_handling.h"

void init(int count){
    mineral_blocks_count = count;
    map_minerals = mineral_blocks_count * 500;

    xpthread_mutex_init(&global_lock);

//    if(pthread_mutex_init(&global_lock, NULL) != 0){
//        perror("pthread_mutex_init()");
//        exit(1);
//    }
    xpthread_mutex_init(&command_lock);

//    if(pthread_mutex_init(&command_lock, NULL)){
//        perror("pthread_mutex_init()");
//        exit(1);
//    }

    mineral_blocks = malloc(sizeof(struct mineral) * mineral_blocks_count);
    for(int i = 0; i < mineral_blocks_count; i++){
        mineral_blocks[i].count = 500;
        xpthread_mutex_init(&mineral_blocks[i].mutex);
        //        if(pthread_mutex_init(&mineral_blocks[i].mutex, NULL) != 0){
//            perror("pthread_mutex_init()");
//            exit(1);
//        }
    }

    for(int i = 0; i < current_thread_count; i++){
        xpthread_create(&threads[i], mine, (void*)i);

//        if(pthread_create(&threads[i], NULL, mine, (void*)i) != 0){
//            perror("pthread_create()");
//            exit(1);
//        }
    }


}


void destroy(){
    for(int i = 0; i < current_thread_count; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_join(input_thread, NULL);
    pthread_join(training_thread, NULL);

    pthread_mutex_destroy(&global_lock);
    pthread_mutex_destroy(&command_lock);

    for(int i = 0; i < mineral_blocks_count; i++){
        pthread_mutex_destroy(&mineral_blocks[i].mutex);
    }

    free(mineral_blocks);
}

void xdestroy(){
    for(int i = 0; i < current_thread_count; i++){
        xpthread_join(threads[i]);
    }
    xpthread_join(input_thread);
    xpthread_join(training_thread);

    xpthread_mutex_destroy(&global_lock);
    xpthread_mutex_destroy(&command_lock);

    for(int i = 0; i < mineral_blocks_count; i++){
        xpthread_mutex_destroy(&mineral_blocks[i].mutex);
    }

    free(mineral_blocks);
}
