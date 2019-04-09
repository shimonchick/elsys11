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

void marine(){
    printf("SCV ready to go, sir!\n");
    xpthread_mutex_lock(&global_lock);
    warriors++;
    
    check_done();

    xpthread_mutex_unlock(&global_lock);

    return;
}
