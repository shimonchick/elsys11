#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
//--------------------------------------------
// NAME: Mihail Kirov
// CLASS: Xib
// NUMBER: 19
// PROBLEM: #1
// FILE NAME: starcraft.c
// FILE PURPOSE:
// starcraft 3 prototype
// ...
//---------------------------------------------
#define MAX_THREAD_COUNT 200
#define INITIAL_WORKER_COUNT 5

typedef void* (*thread_fun_t)(void*);
 
struct data{
    thread_fun_t fun;
    int sleep_time;
};
struct mineral_t{
    pthread_mutex_t mutex;
    int count;
};

pthread_t threads[MAX_THREAD_COUNT];

pthread_t training_thread;

struct mineral_t* mineral_blocks;
int warriors = 0;
int mineral_blocks_count = 2;

int minerals = 0;

int current_thread_count = INITIAL_WORKER_COUNT;

pthread_mutex_t global_mutex;
pthread_mutex_t command_lock;

int min(int a, int b){
    return a <=b ? a : b;
}

//--------------------------------------------
// FUNCTION: are_minerals_empty
// checks the local mineral status of a miner returns whether or not they are empty
// PARAMETERS:
// mineral_status --> the local mineral status of each miner
//----------------------------------------------
int are_minerals_empty(int mineral_status[mineral_blocks_count]){
    for(int i = 0; i < mineral_blocks_count; i++){
        if(mineral_status[i] == 1){
            return 0;
        }
    }
    return 1;
}
//--------------------------------------------
// FUNCTION: mine
// Thread function that mines all available mineral blocks and adds the minerals to the total
// PARAMETERS:
// miner_number -> the number of the thread + 1
//----------------------------------------------
void* mine(void* arg){
    printf("You wanna piece of me, boy?\n");
    int miner_number = (int)arg + 1;

    int minerals_status[mineral_blocks_count];
    for(int i = 0; i < mineral_blocks_count; i++){
        minerals_status[i] = 1; // 1- full, 0 - empty
    }
    
    while(!are_minerals_empty(minerals_status)){
        for(int mineral_index = 0; mineral_index < mineral_blocks_count; mineral_index++){
            if(minerals_status[mineral_index] <= 0){
                continue;
            }
            
            sleep(3);
            
            if(pthread_mutex_trylock(&(mineral_blocks[mineral_index].mutex))){
                if(mineral_blocks[mineral_index].count <= 0){
                    minerals_status[mineral_index] = 0;
                    pthread_mutex_unlock(&mineral_blocks->mutex);
                
                }
                else{
                    printf("SCV %d is mining from mineral block %d\n", miner_number, mineral_index);
                    int minerals_taken = min(mineral_blocks[mineral_index].count, 8);
                    
                    mineral_blocks[mineral_index].count -= minerals_taken;
                    if(mineral_blocks[mineral_index].count <= 0){
                        minerals_status[mineral_index] = 0;
                    }
                    pthread_mutex_unlock(&mineral_blocks->mutex);
                    printf("SCV %d is transporting minerals\n", miner_number);
                    sleep(2);
                    pthread_mutex_lock(&global_mutex);
                        minerals += minerals_taken;
                    pthread_mutex_unlock(&global_mutex);
                    printf("SCV %d delivered minerals to Command center\n", miner_number);
                } 
            }

        }
        


    }

    return NULL;
}
void init(int count){
    mineral_blocks_count = count; 
    
    pthread_mutex_init(&global_mutex, NULL);
    pthread_mutex_init(&command_lock, NULL);
    
    mineral_blocks = malloc(sizeof(struct mineral_t) * mineral_blocks_count);
    for(int i = 0; i < mineral_blocks_count; i++){
        mineral_blocks[i].count = 500;
        pthread_mutex_init(&mineral_blocks[i].mutex, NULL);
    }
     
    for(int i = 0; i < current_thread_count; i++){
        pthread_create(&threads[i], NULL, mine, (void*)i);
    }

}
void destroy(){
    for(int i = 0; i < current_thread_count; i++){
        pthread_join(threads[i], NULL);
    }
    //join command center threads
    pthread_mutex_destroy(&global_mutex);
    pthread_mutex_destroy(&command_lock);
    for(int i = 0; i < mineral_blocks_count; i++){
        pthread_mutex_destroy(&mineral_blocks[i].mutex);
    }
    free(mineral_blocks);
}
void* create_unit(void* args){
    struct data data = *(struct data*)args;
    sleep(data.sleep_time);
    int done = false;
    pthread_mutex_lock(&global_mutex);
        if(minerals >= 50){
            minerals -= 50;
        }
        else{
            printf("Not enough minerals\n");
            done = true;
        }
    pthread_mutex_unlock(&global_mutex);
    if(done){
        return NULL;
    }
    current_thread_count++;
    pthread_create(&threads[current_thread_count - 1], NULL, data.fun, current_thread_count);
  //  if(func){
  //      func(arg);
  //  }
    return NULL;
}
void* marine(void* arg){
    printf("SCV ready to go, sir!\n");

    warriors++;
    
    while(true){
        pthread_mutex_lock(&global_mutex);
            
        if(warriors == 20){
            destroy();
            exit(0);
        }

        pthread_mutex_unlock(&global_mutex);

    }
}
int main(int argc, char* argv[]){
    int mineral_count = 2;
    if(argc == 2){
        mineral_count = atoi(argv[1]);
    }
    init(mineral_count);
    int done = false;
    while(!done){
        char command;
        scanf("%c\n", &command);
        switch(command) {
            case 'q':
                //println("%d\n", done = true);             
                done = true;
                break;
            case 's':
                ;
                
                struct data data = {
                    mine, 4
                };
                pthread_create(&training_thread, NULL,
                        create_unit, &data); 
                pthread_join(training_thread, NULL);
                //create_unit(mine, 4);
                break;
            case 'm':
                //create_unit(marine, 1);
                break;

        }
    //    if(command == 'm'){
    //        pthread_mutex_lock(&global_mutex);
    //            if(minerals >= 50){
    //                minerals -= 50;
    //                printf("You wanna piece of me, boy?\n");
    //            }
    //            else{
    //                printf("Not enough minerals\n");
    //            }
    //            pthread_mutex_unlock(&global_mutex);
    //        sleep(1);
    //    }
    //    else if(command == 's'){
    //        sleep(4);
    //        pthread_mutex_lock(&global_mutex);
    //        if(minerals >= 50){
    //            minerals -= 50;
    //        }
    //        pthread_mutex_unlock(&global_mutex);
    //        current_worker_count++;
    //        pthread_create(workers[current_worker_count], NULL, mine, (void*)current_worker_count);
    //        printf("SCV ready to go, sir!\n");
    //    }
    }
    destroy();
    printf("Map minerals %d, player minerals %d, SCVs %d, Marines %d\n", mineral_blocks_count * 500,  minerals, current_thread_count, warriors);
    exit(0);
}
