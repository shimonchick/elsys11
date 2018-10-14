
//------------------------------------------------------------------------
// NAME: Mihail Kirov
// CLASS: XIb
// NUMBER: 19
// PROBLEM: #4
// FILE NAME: void_swap.c
// FILE PURPOSE:
// function swaps the values of 2 variables of same type
// FUNCTION: void swap(void* a, void* b, size_t size);
// PARAMETERS: 2 pointers to variables of same size and the size(in bytes) of their type
//------------------------------------------------------------------------

#include <stddef.h> // declares size_t structure
#include <stdio.h>
#include <stdlib.h>
void swap(void* a, void* b, size_t size){
    char* temp_a = a; //casting void* to char* (size of char is  1);
    char* temp_b = b;
    char* temp_c;
    for(size_t i = 0; i < size; i++){
        temp_c = temp_a[i];
        temp_a[i] = temp_b[i];
        temp_b[i] = temp_c;
    }
}

int main(){
    int a = 5;
    int b = 10;
    float c = 34.5;
    float d = 12.543;
    printf("a: %d, b: %d\n", a, b);
    swap(&a,&b, sizeof(a));
    printf("a: %d, b: %d\n", a, b);
    swap(&c,&d, sizeof(c));
    printf("a: %d, b: %d\n", a, b);
     
    return 0;

}
