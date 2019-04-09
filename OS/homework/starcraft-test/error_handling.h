//
// Created by misho on 30/03/19.
//

#ifndef INC_2019_3_26_ERROR_HANDLING_H
#define INC_2019_3_26_ERROR_HANDLING_H

#include <zconf.h>

typedef void* (*thread_fun_t)(void*);

//pthread_mutex_init with error checking
void xpthread_mutex_init(pthread_mutex_t*);

//pthread_mutex_destroy with error checking
void xpthread_mutex_destroy(pthread_mutex_t*);

//pthread_mutex_lock with error checking
void xpthread_mutex_lock(pthread_mutex_t*);

//pthread_mutex_unlock with error checking
void xpthread_mutex_unlock(pthread_mutex_t*);

//pthread_create with error checking
void xpthread_create(pthread_t* thread, thread_fun_t fun, void* args);

//pthread_join with error handling
void xpthread_join(pthread_t thread);

#endif //INC_2019_3_26_ERROR_HANDLING_H
