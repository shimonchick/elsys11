#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define true 1

int is_prime(int n){
    if(n <= 2) return 0;
    for(int i = 3; i < n; i++){
        if(n % i == 0){
            return 0;
        }
    }
    return 1;
}
void* get_number_of_primes(void* arg){
    int n = (int)arg;
    int result = 0;
    for(int i = 1; i < n; i++){
        if(is_prime(i)){
            result++;
        }
    }
    printf("Number of primes for N=%d is %d\n", n, result);
    return NULL;
}


int main(){

    char command;
    pthread_t worker_thread[100];
    int thread_number = 0;
    while(true){
        scanf("%c", &command);
        if(command == 'p'){
            
            int n;
            scanf("%d", &n);
            pthread_create(&worker_thread[thread_number % 5]
                    , NULL, get_number_of_primes,
                    (void*)n);
            thread_number++;
            printf("Prime calculator started with N=%d\n", n);
        }
        else if(command == 'e'){
            for(int i = 0; i < thread_number; i++){ 
                pthread_join(worker_thread[i], NULL);
            }
            exit(0);
        }
    }

    exit(0);
}
