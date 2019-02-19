#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define THREADS_COUNT 5

void* helloworld(void* arg){
    printf("Hello world\n");
    return NULL;
}
int main(){

    pthread_t threads[THREADS_COUNT];
    for(int i = 0; i < THREADS_COUNT; i++){
        pthread_create(&threads[i], NULL, helloworld, NULL);
    
    }
    for(int i = 0; i < THREADS_COUNT; i++){
        pthread_join(threads[i], NULL);
    }
    exit(0);
}


