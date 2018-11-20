//------------------------------------------------------------------------
// NAME: Mihail Kirov
// CLASS: XIb
// NUMBER: 19
// PROBLEM: #2
// FILE NAME: head_with_headers.c
// FILE PURPOSE:
// prints the first 10 lines of a multiple files to standard output.
//------------------------------------------------------------------------
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096
#define FILENAME_SIZE 50
//------------------------------------------------------------------------
// FUNCTION: head
// prints the first 10 lines of a function to the standard output
// PARAMETERS:
// const char* filename --> the name of the file, which we want use.
//------------------------------------------------------------------------
void head(const char* filename){
    char buffer[BUFFER_SIZE];
    char* pos = buffer;
    int remaining = BUFFER_SIZE;
    int fd;
    if((fd = open(filename,  O_NONBLOCK | O_RDONLY)) < 0)
    {
        perror("open");
        exit(1);
    }

    int lines = 0;
    ssize_t bytes_read = 0; 
    while((bytes_read = read(fd, pos, remaining)) != 0){
        pos += bytes_read;
        remaining -= bytes_read;
        int i = 0;
        while(i < bytes_read && lines != 10){
            if (buffer[i++] == '\n'){
                lines++;
            }
        }
        write(STDOUT_FILENO, buffer, i);
    }
    close(fd);
    

}
//------------------------------------------------------------------------
// FUNCTION: main
// prints the file names and calls the head function
// PARAMETERS:
// argc ---> console argument count ; argv ---> console arguments
//------------------------------------------------------------------------

int main(int argc, char* argv[]){
    if(argc == 2){ // only 1 file
        head(argv[1]);
    }
    else{
        for(int i = 1; i < argc; i++ ){
            char filename_buffer[FILENAME_SIZE + 12] = "==> ";
            strcat(filename_buffer, argv[i]);
            strcat(filename_buffer, " <==\n");
            
            write(STDOUT_FILENO, filename_buffer, strlen(filename_buffer));
            
            head(argv[i]);
            if(i != argc - 1 ){
                write(STDOUT_FILENO, "\n", 1);
            }
        }

    }
    return 0;
}

