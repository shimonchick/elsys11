#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct{
    int* data;
    int size;
} list;

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
// argv[1] = number of array elements
// argv[2] = number of threads
int main(int argc, char* argv[]){
    //generate random array
    time_t t;
    srand((unsigned) time(&t));
    int count = atoi(argv[1]);
    printf("count: %d\n", count);
    int* data = malloc(sizeof(int) * count);
    
    for(int i = 0; i < count; i++){
        data[i] = rand() % 100;    
        printf("%d ", data[i]);
    }
    printf("\ntest 1\n");
    int thread_count = MIN(atoi(argv[2]), count);
    pthread_t threads[thread_count];
    
    list partitions[thread_count];
    for(int i = 0; i < thread_count; i++){
        partitions[i].data = data + (count/thread_count)*i;
        partitions[i].size = count/thread_count;
        pthread_create(&threads[i], NULL, sort_array, &partitions[i]);
    }

    
    for(int i = 0; i < thread_count; i++){
        pthread_join(threads[i], NULL);
    }
    
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
    int result[count];
    for(int i = 0; i < count; i++){
        int min_index = 0;
        for(int j = 1; j < thread_count; j++){
            if(indexes[j] == count/thread_count){
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
 //   int index_first = 0, index_second = 0;
 //   int result[count];
 //   for(int i = 0; i < count; i++){
 //       if(list1.data[index_first] < list2.data[index_second]){
 //           result[i] = list1.data[index_first];
 //           index_first++;
 //       }
 //       else{
 //           result[i] = list2.data[index_second];
 //           index_second++;
 //       }
 //   }
    for(int i = 0; i < count; i++){
        printf("%d ", result[i]);
    }

    free(data);

}
