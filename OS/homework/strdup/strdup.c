//------------------------------------------------------------------------
// NAME: Mihail Kirov
// CLASS: XIb
// NUMBER: 19
// PROBLEM: #5
// FILE NAME: strdup.c
// FILE PURPOSE:
// function that duplicates a C style string using dynamic memory
// FUNCTION: char* strdup(const char*);
// PARAMETERS: const char * --> C style string we want to copy
//------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

//returns the length of C string excluding '\0'
size_t strlen(const char* str){
    size_t i = 0;
    while(str[i]!='\0'){
        i++;
    }
    return i;
}

char* strdup(const char* other){
    char* duplicate = malloc(sizeof(char) * strlen(other) + 1); // +1 to include the \0 
    int i = 0;
    while(other[i]!= '\0'){
        duplicate[i] = other[i];
        i++;
    }
    duplicate[i] = other[i]; // duplicate '\0'
    return duplicate;
}
int main(){
    char* a = "something";
    char* b = strdup(a);
    printf("%s\n", b);
    return 0;
}
