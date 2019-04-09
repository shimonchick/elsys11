//
// Created by misho on 30/03/19.
//

#include <pthread.h>
#include <stdio.h>
#include "error_handling.h"
#include <stdlib.h>

void xpthread_mutex_destroy(pthread_mutex_t* mutex) {
    if(pthread_mutex_destroy(mutex) != 0){
        perror("pthread_mutex_destroy()");
        exit(1);
    }
}

void xpthread_mutex_init(pthread_mutex_t* mutex) {
    if(pthread_mutex_init(mutex, NULL) != 0){
        perror("pthread_mutex_init()");
        exit(1);
    }
}

void xpthread_mutex_lock(pthread_mutex_t * mutex) {
    if(pthread_mutex_lock(mutex) != 0){
        perror("pthread_mutex_lock()");
        exit(1);
    }
}

void xpthread_mutex_unlock(pthread_mutex_t * mutex) {
    if(pthread_mutex_unlock(mutex) != 0){
        perror("pthread_mutex_unlock()");
        exit(1);
    }
}

void xpthread_create(pthread_t *thread, thread_fun_t fun, void *args) {
    if(pthread_create(thread, NULL, fun, args) != 0){
        perror("pthread_create()");
        exit(1);
    }
}

void xpthread_join(pthread_t thread){
    if(pthread_join(thread, NULL) != 0){
        perror("pthread_join()");
        exit(1);
    }
}

