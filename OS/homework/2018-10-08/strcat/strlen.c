//------------------------------------------------------------------------
// NAME: Mihail Kirov
// CLASS: XIb
// NUMBER: 19
// PROBLEM: #1
// FILE NAME: strlen.c
// FILE PURPOSE:
// function that calculates the length of a C style string
// FUNCTION: size_t strlen(const char*);
// PARAMETERS: const char * --> array of characters, whose size we want to get
//------------------------------------------------------------------------
#include "strlen.h" // function declaration and size_t declaration
size_t strlen(const char* str){
    size_t i = 0;
    while(str[i]!='\0'){
        i++;
    }
    return i;
}

