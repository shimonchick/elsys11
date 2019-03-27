#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define true 1


#define CAR_COUNT 5
pthread_mutex_t cars[CAR_COUNT];
int car_state[CAR_COUNT];
#define DRIVER_COUNT 20

int isDone(int car_state[5]){
    for(int i = 0; i < 5; i++){
        if(car_state[i] == 0){
            return 0;
        }
    }
    return 1;
}
void* drive(void* arg){

    int driver_number = (int)arg + 1;
    int isFinished = 0;
    int car_state[5] = { 0, 0, 0, 0, 0};
    int i = 0;
    while(!isFinished){
        i = i % CAR_COUNT;
        if(car_state[i]){
            i++;
            continue;
        }
        if(pthread_mutex_trylock(&cars[i]) == 0){
            printf("Buyer %d takes car %d.\n", driver_number, i + 1);
            car_state[i] = 1;
            if(isDone(car_state)){
                isFinished = 1;
            }

            sleep(1);
            //printf("Buyer %d returns car %d", driver_number, i + 1);
            pthread_mutex_unlock(&cars[i]);
            printf("Buyer %d returns car %d.\n", driver_number, i + 1);
        
        }
        i++;
    }
    return NULL;
}

int main(){
    for(int i = 0; i < CAR_COUNT; i++){
        pthread_mutex_init(&cars[i], NULL);
    }
    pthread_t driver_threads[DRIVER_COUNT];
    for(int i  = 0; i < DRIVER_COUNT; i++){
        pthread_create(&driver_threads[i], NULL, drive, (void*)i);
    }
    for(int i = 0; i < DRIVER_COUNT; i++){
        pthread_join(driver_threads[i], NULL);
    }
    for(int i = 0; i < CAR_COUNT; i++){
        pthread_mutex_destroy(&cars[i]);
    }
}
