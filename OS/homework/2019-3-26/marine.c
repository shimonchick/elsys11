//
// Created by misho on 29/03/19.
//

#include "marine.h"
#include "helper.h"
#include "command_center.h"
#include "error_handling.h"
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void* marine(void* arg){
    printf("SCV ready to go, sir!\n");
    xpthread_mutex_lock(&global_lock);
    warriors++;
    if(warriors == 20){
        done = true;
    }
    xpthread_mutex_unlock(&global_lock);

    return NULL;
}