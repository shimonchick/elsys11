
//------------------------------------------------------------------------
// NAME: Mihail Kirov
// CLASS: XIb
// NUMBER: 19
// PROBLEM: #6
// FILE NAME: stack.c
// FILE PURPOSE:
// stack implementation
// FUNCTIONS: 
// void stack_init(stack*);
// initializes stack
// void stack_destroy(stack*);
// clears up memory for stack
// void stack_empty(stack*);
// checks if the stack is empty
// void stack_push(stack*, int);
// pushes an element on the stack
// int stack_top(stack*);
// returns the top element of the stack if there is one
// int stack_pop(stack*);
// returns the top element of the stack if there is one , removing it from the stack
//
// PARAMETERS:
// stack* --> pointer to the stack structure we want to modify
// int --> value to push to stack 
//------------------------------------------------------------------------
#include <stddef.h> // size_t declaration
#include <stdlib.h>
#include <stdio.h>
struct stack{
    size_t capacity;
    size_t size;
    int* elements;
};

typedef struct stack stack; // to write stack instead of struct stack

void stack_init(stack*);
void stack_destroy(stack*);
int stack_empty(stack*);
void stack_push(stack*, int);
int stack_top(stack*);
int stack_pop(stack*);


void stack_init(stack* stack){
    stack->size = 0;
    stack->capacity = 0;
    stack->elements = NULL;
}
void stack_destroy(stack* stack){
    stack->size = 0;
    stack->capacity = 0;
    free(stack->elements); 
}
int stack_empty(stack* stack){
    return stack->size == 0;
}

void stack_push(stack* stack, int value){
    if(stack->size == stack->capacity){
        if(stack->capacity == 0){
            stack->capacity = 1;
        }
        else{
            stack->capacity *= 2;
        }
    }
    stack->elements = malloc(sizeof(int) * stack->capacity);
    stack->elements[stack->size] = value;
    stack->size++;
}

int stack_top(stack* stack){
    if(!stack_empty(stack)){
        return stack->elements[stack->size - 1];
    }
}

int stack_pop(stack* stack){
    if(!stack_empty(stack)){
        stack->size --;
        return stack->elements[stack->size];
    }
}
int main(){
    stack st;
    stack_init(&st);
    stack_push(&st, 3);
    stack_push(&st, 5);

    stack_destroy(&st);
    return 0;
}
