#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
//------------------------------------------------------------------------
// NAME: Mihail Kirov
// CLASS: XIb
// NUMBER: 19
// PROBLEM: #1
// FILE NAME: sort.c
// FILE PURPOSE:
// sorts an array on multiple threads
//------------------------------------------------------------------------
typedef struct{
    int* data;
    int size;
} list;
//------------------------------------------------------------------------
// FUNCTION: sort_array
// sorts a given array using bubble sort
// PARAMETERS:
// void* arg --> pointer to the data to be sorted
//------------------------------------------------------------------------
void* sort_array(void* arg){
    list* list1 = (list*)arg;
    for(int i = 0; i < list1->size - 1; i++){
        for(int j = 0; j < list1->size - i - 1; j++){
            if(list1->data[j] > list1->data[j + 1]){
                int temp = list1->data[j];
                list1->data[j] = list1->data[j+1];
                list1->data[j + 1] = temp;
            }
        }
    }
    
    return NULL;
}

//generates an array of @count elements in dynamic memory
//array must be freed manually
int* generate_random_array(int count){

    time_t t;
    srand((unsigned) time(&t));
    int* data = malloc(sizeof(int) * count);
    
    for(int i = 0; i < count; i++){
        data[i] = rand() % 100;    
        printf("%d ", data[i]);
    }
    return data;
}

//------------------------------------------------------------------------
// FUNCTION: main
// generates, partitions and merges the array to be sorted
// PARAMETERS:
// argv[1] = number of array elements
// argv[2] = number of threads
//------------------------------------------------------------------------
int main(int argc, char* argv[]){
    //generate random array
    int count = atoi(argv[1]);
    int* data = generate_random_array(count);

    int thread_count = MIN(atoi(argv[2]), atoi(argv[1])); // min of number of threads and number of elements;
    
    pthread_t threads[thread_count];
    
    //partition the data to be sorted and call sort function on separate thread
    list partitions[thread_count];
    for(int i = 0; i < thread_count; i++){
        partitions[i].data = data + (count/thread_count)*i;
        partitions[i].size = count/thread_count;
        pthread_create(&threads[i], NULL, sort_array, &partitions[i]);
    }

    //wait for all threads to finish
    for(int i = 0; i < thread_count; i++){
        pthread_join(threads[i], NULL);
    }
    //test prints
    for(int i = 0; i < thread_count; i++){
        printf("\npartition %d values:\n", i);
        for(int j = 0; j < partitions[i].size; j++){
            printf("%d ", partitions[i].data[j]);
        }
    } 
    printf("\n");

    int indexes[thread_count];
    //default index values;
    for(int i = 0; i < thread_count; i++){
        indexes[i] = 0;
    }
    //merge all partitions
    int result[count];
    for(int i = 0; i < count; i++){
        int min_index;
        for(int j = 0; j < thread_count; j++){
            if(indexes[j] < count/thread_count){
                min_index = j;
                break;
            }
        }
        for(int j = 1; j < thread_count; j++){
            if(indexes[j] == count/thread_count){
                continue;

            }
            if(indexes[min_index] == count/thread_count){
                continue;
            }
            if(partitions[j].data[indexes[j]] < partitions[min_index].data[indexes[min_index]]){
                min_index = j;
            }
        }
        result[i] = partitions[min_index].data[indexes[min_index]];
        if(indexes[min_index] < count/thread_count){
            indexes[min_index]++;
        }
        
    }
    //print the result
    for(int i = 0; i < count; i++){
        printf("%d ", result[i]);
    }

    free(data);

}
