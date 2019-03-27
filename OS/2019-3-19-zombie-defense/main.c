#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define true 1

pthread_mutex_t mutex;
int gold = 100;
int soldiers = 0;
int hp = 100;

void* mine(void* arg){
    while(true){
        pthread_mutex_lock(&mutex);
        
        gold += 10;
        print_gold(gold);
    
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }  
    return NULL;
}

void* attack(void* arg){
  //  int allowed = 0;
  //  while(!allowed){
  //      pthread_mutex_lock(&mutex);
  //      if(gold > 100){
  //          allowed = 1;
  //      }
  //      pthread_mutex_unlock(&mutex);
  //  }
    int zombie_count = 1;
    while(true){
        for(int i = 0; i < 5;i++){
            print_zombies(i, zombie_count);
            sleep(1);
        }

        pthread_mutex_lock(&mutex);
        if(soldiers >= zombie_count){
            print_succ("Zombie attack deflected :)!");
        }
        else{
            print_fail("Zombie attack succeded :(!");
            int hp_loss = zombie_count - soldiers;
            hp -= hp_loss;
            print_health(hp);
            if(hp <= 0){
                game_end(zombie_count);
            }
        }
        pthread_mutex_unlock(&mutex);
        zombie_count *= 2;
    }
    return NULL;
}
int main() {
	init();
    pthread_t threads[100];
    pthread_t zombie_thread[1];
    int current_thread = 0;
    pthread_mutex_lock(&mutex);
        print_gold(gold);
        print_health(hp);
        print_soldiers(soldiers);

    pthread_mutex_unlock(&mutex);
    pthread_create(&zombie_thread[0], NULL, attack, NULL);
	while(1) {
		int ch = get_input();
		switch(ch) {
            case 'm':
                pthread_mutex_lock(&mutex);
                if(gold >= 100){
                    gold -= 100;
                    print_gold(gold);
                    pthread_create(&threads[current_thread], NULL, mine, NULL);
                    current_thread++;
                    print_msg("Miner created!");
                }
                else{
                    print_fail("Not enough gold!");
                }
                pthread_mutex_unlock(&mutex);

                break;
            case 's':
                pthread_mutex_lock(&mutex);
                if(gold >= 10){
                    soldiers++;
                    print_soldiers(soldiers);
                    gold -= 10;
                    print_gold(gold);
                }
                else{
                    print_fail("Not enough gold!");

                }
                pthread_mutex_unlock(&mutex);

                break;
            case 'x':
                pthread_mutex_lock(&mutex);
                if(gold >= 100){
                    soldiers+= 10;
                    print_soldiers(soldiers);
                    gold -= 100;
                    print_gold(gold);
                }
                else{
                    print_fail("Not enough gold!");

                }
                pthread_mutex_unlock(&mutex);
                break;
            case 'q':
				game_end(1);
				break;
		
        }
	}

}
