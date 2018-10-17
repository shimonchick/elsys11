//------------------------------------------------------------------------
// NAME: Mihail Kirov
// CLASS: XIb
// NUMBER: 19
// PROBLEM: #2
// FILE NAME: strcat.c
// FILE PURPOSE:
// function that concatenates two C style strings
// FUNCTION: char* strcat(char*, const char*);
// PARAMETERS: char* for destination char array and const char* for source char array
//------------------------------------------------------------------------
#include "stdio.h"
#include <stddef.h> // defines size_t
//returns the length of C string excluding '\0'
//helper function
size_t strlen(const char* str){
    size_t i = 0;
    while(str[i]!='\0'){
        i++;
    }
    return i;
}
// concatenates string source to string destination and returns pointer to destination
char* strcat(char* destination, const char* source){
    int destination_length = strlen(destination);
    for(int i = 0; i < strlen(source); i ++){
        destination[destination_length + i] = source[i];
    }
    return destination;
}

int main(){
    char str1[20] = "some";
    char* str2 = "thing";
    strcat(str1, str2);
    printf("%s", str1);
    return 0;
}
