//------------------------------------------------------------------------
// NAME: Mihail Kirov
// CLASS: XIb
// NUMBER: 19
// PROBLEM: #1
// FILE NAME: bmp-info.c
// FILE PURPOSE:
// get the width and height of BMP image
//------------------------------------------------------------------------
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//------------------------------------------------------------------------
// FUNCTION: read_image
// opens the path pointed to by filepath, reads the file and saves it to an array. Returns a pointer to that array
// PARAMETERS:
// const char* filepath -> path to the file we want to open
//------------------------------------------------------------------------
void* read_image(const char*);

//------------------------------------------------------------------------
// FUNCTION: main
// opens a bmp file given as parameter, reads it and returns the width and height of the file; 
// PARAMETERS:
// argc -> argument count, argv -> list of parmeter strings, argv[1] should be the filepath
//------------------------------------------------------------------------
int main(int argc, char* argv[]){
    if(argc == 2){ // ensure that we have a parameter
        char* file = (char*)read_image(argv[1]);
        if(file){
            int32_t* width = (int32_t*)(file + 18);
            int32_t* height = (int32_t*)(file + 22);

            printf("BMP image width: %d\n", *width);
            printf("BMP image height: %d\n", *height);
             
            free(file);
        }
        else{
            printf("could not open file");

        }
    }
    return 0;

}

