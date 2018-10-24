
//------------------------------------------------------------------------
// NAME: Mihail Kirov
// CLASS: XIb
// NUMBER: 19
// PROBLEM: #2
// FILE NAME: png-info.c
// FILE PURPOSE:
// get the width and height of PNG image
//------------------------------------------------------------------------
#include <stdint.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
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
// opens a png file given as parameter, reads it and returns the width and height of the file; 
// PARAMETERS:
// argc -> argument count, argv -> list of parmeter strings, argv[1] should be the filepath
//------------------------------------------------------------------------

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Unable to open file");
        return 1;
    }
    else{
        unsigned char png_signature_codes[8] = {'\x89', '\x50', '\x4E', '\x47', '\x0D', '\x0A', '\x1A', '\x0A' };
        unsigned char* file = (unsigned char*)read_image(argv[1]);
        uint32_t* width_ptr;
        uint32_t* height_ptr;
        uint32_t width, height;
        if(file == NULL){
            printf("Unable to open file");
            return 1;
        }
        int offset = 0;
        for( ; offset < 8; offset++){
            //printf("is: %d should be: %d\n", (unsigned char)file[offset], png_signature_codes[offset]);
            if((unsigned char)file[offset] != png_signature_codes[offset]){
                printf("Unable to parse file");
                return 1;
            }
        }
        int done = 0;
        while(!done){
            uint32_t* block_size_ptr = (uint32_t*)(file + offset);
            uint32_t block_size = ntohl(*block_size_ptr);
            //printf("block size: %d\n", block_size);
            offset +=4; // moving 4 bytes after reading block size;
            char block_type[5];
            for(int i = 0; i < 4; i++){
                block_type[i] = file[offset + i];
            }
            block_type[4] = '\0';
            offset += 4; // moving 4 bytes after reading block type
            //printf("%s\n", block_type);
            if(strcmp(block_type, "IHDR") == 0){
                width_ptr = (uint32_t*)(file + offset);
                height_ptr = (uint32_t*)(file + offset + 4);
                width = ntohl(*width_ptr);
                height = ntohl(*height_ptr);
                
            }
            if(strcmp(block_type, "IEND") == 0){
                done = 1;
            }
            for(int i = 0; i < block_size; offset++, i++) // move block_size bytes forward
            {
                //printf("moving a byte forward \n");
            }            
            offset += 4; // move 4 bytes forward for CRC
        }
        printf("PNG image width: %d\n", width);
        printf("PNG image height: %d\n", height);
        printf("PNG file size: %d\n", offset);
        free(file);            
    }
    return 0;
}
