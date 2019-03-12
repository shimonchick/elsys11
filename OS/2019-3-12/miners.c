#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
//--------------------------------------------
// NAME: Mihail Kirov
// CLASS: XI b
// NUMBER: 19
// PROBLEM: #1
//---------------------------------------------
int money = 0;
pthread_mutex_t mutex;

void* mine(void* arg){
    int i = (int)arg + 1;
    for(int j = 0; j < 20; j++){
        pthread_mutex_lock(&mutex);
        
        money += 10;
    
        pthread_mutex_unlock(&mutex);
        printf("Miner %d gathered 10 gold\n", i); 
        sleep(2);
    }  
    return NULL;
}

void* sell(void* arg){
    int i = (int)arg + 1;
    for(int j = 0; j < 20; j++){
        int done = 0;
        while(!done){
            pthread_mutex_lock(&mutex);
            if(money < 10){
                printf("The warehouse is empty, cannot sell!\n");
            }
            else{
                money -= 10;  
                printf("Trader %d sold 10 gold\n", i); 
                done = 1;
            }
            pthread_mutex_unlock(&mutex);
            sleep(2);
        }
        
    }   
    return NULL;

}
int main(int argc, char* argv[]){


    pthread_mutex_init(&mutex, NULL);

    int miner_count = 1; 
    int seller_count = 1;
    if(argc == 3){
        miner_count = atoi(argv[1]);
        seller_count = atoi(argv[2]);
    }
    
    pthread_t miner_threads[miner_count];
    pthread_t seller_threads[seller_count];
    for(int i = 0 ; i <miner_count; i++){
        pthread_create(&miner_threads[i], NULL, mine, (void*)i);
    }
    for(int i = 0; i < seller_count; i++){
        pthread_create(&seller_threads[i], NULL, sell, (void*)i);
    }
    for(int i = 0 ; i <miner_count; i++){
        pthread_join(miner_threads[i], NULL);
    }
    for(int i = 0; i < seller_count; i++){
        pthread_join(seller_threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);

    printf("Gold: %d", money);
    exit(0);
}
