//------------------------------------------------------------------------
// NAME: Mihail Kirov
// CLASS: XIb
// NUMBER: 19
// PROBLEM: #3
// FILE NAME: swap.c
// FILE PURPOSE:
// function that swaps the values of two integers;
// FUNCTION: void swap(int* a, int* b)
// PARAMETERS: pointer to the first and second integers
//------------------------------------------------------------------------
#include <stdio.h>
void swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}

int main(){
    int a = 5;
    int b = 10;
    printf("%d, %d\n", a, b);
    swap(&a, &b);
    printf("%d, %d\n", a, b);

}
