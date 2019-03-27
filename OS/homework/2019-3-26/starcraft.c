#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define INITIAL_WORKER_COUNT 5
#define true 1


struct mineral_t{
    pthread_mutex_t mutex;
    int count;
};

struct mineral_t* mineral_blocks;
int warriors = 0;
int mineral_blocks_count = 2;

int minerals = 0;

pthread_mutex_t global_mutex;
int min(int a, int b){
    return a <=b ? a : b;
}
int are_minerals_empty(int mineral_status[mineral_blocks_count]){
    for(int i = 0; i < mineral_blocks_count; i++){
        if(mineral_status[i] == 1){
            return 0;
        }
    }
    return 1;
}
void* mine(void* arg){
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
                    printf("CSV %d is mining from mineral block %d\n", miner_number, mineral_index);
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
int game_finished(){
    int is_finished = 1;
    pthread_mutex_lock(&global_mutex);
    for(int i = 0; i < mineral_blocks_count; i++){
        if(mineral_blocks[i].count > 0){
            is_finished = 0;
            break;
        }
    }
    if(warriors < 20){
        is_finished = 0;
    }
    pthread_mutex_unlock(&global_mutex);
    return is_finished; 
}


int main(int argc, char* argv[]){
    
    pthread_mutex_init(&global_mutex, NULL);

    if(argc == 2){
        mineral_blocks_count = atoi(argv[1]);
    }
    
    mineral_blocks = malloc(sizeof(struct mineral_t) * mineral_blocks_count);
    for(int i = 0; i < mineral_blocks_count; i++){
        mineral_blocks[i].count = 10; // 500
        pthread_mutex_init(&mineral_blocks[i].mutex, NULL);
    }
    int worker_count = INITIAL_WORKER_COUNT;
    
    pthread_t* workers;
    workers = malloc(sizeof(pthread_t) * worker_count);
    for(int i = 0; i < worker_count; i++){
        pthread_create(&workers[i], NULL, mine, i);
    }
     
    while(true){
        char command;
        scanf("%c\n", &command);

        if(command == 'm'){
            pthread_mutex_lock(&global_mutex);
                if(minerals >= 50){
                    minerals -= 50;
                    warriors++;
                    if(warriors == 20){
                        break;
                    }
                    printf("You wanna piece of me, boy?\n");
                }
                else{
                    printf("Not enough minerals\n");
                }
                pthread_mutex_unlock(&global_mutex);
            sleep(2);
        }
        if(command == 's'){
            pthread_mutex_lock(&global_mutex);
            if(minerals >= 50){
                minerals -= 50;
            }

        }
    }
    for(int i = 0; i < worker_count; i++){
        pthread_join(workers[i], NULL);
    }
    printf("Map minerals %d, player minerals %d, SCVs %d, Marines %d\n", mineral_blocks_count * 500,  minerals, worker_count, warriors);
    exit(0);
}
