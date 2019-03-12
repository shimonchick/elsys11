#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#define SIZE 1000000

double sum;
pthread_mutex_t mutex;

void* sumfunc(void* arg){
    
    for(int i = 0; i < SIZE; i++){
        //double temp = sin(i) * sin(i) + cos(i) * cos(i);  
        pthread_mutex_lock(&mutex);
        sum += sin(i) * sin(i) + cos(i) * cos(i);  
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(){
    pthread_t threads[2];
    pthread_mutex_init(&mutex, NULL);
    for(int i = 0; i  < 2; i++){
        pthread_create(&threads[i], NULL, sumfunc, NULL);
    }
    for(int i = 0; i  < 2; i++){
        pthread_join(threads[i], NULL);
    }
    printf("sum%f\n", sum);
    pthread_mutex_destroy(&mutex); 
    exit(0);
}
