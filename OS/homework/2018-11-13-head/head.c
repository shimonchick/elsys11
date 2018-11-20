//------------------------------------------------------------------------
// NAME: Mihail Kirov
// CLASS: XIb
// NUMBER: 19
// PROBLEM: #1
// FILE NAME: head.c
// FILE PURPOSE:
// prints the first 10 lines of a file to standard output.
//------------------------------------------------------------------------


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096
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
int main(){
    head("a.txt");
    return 0;
}
