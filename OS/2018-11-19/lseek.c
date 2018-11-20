//------------------------------------------------------------------------
// NAME: Mihail Kirov
// CLASS: XIb
// NUMBER: 19
// PROBLEM: #1
// FILE NAME: lseek.c
// FILE PURPOSE:
// reads a file given as parameter and decrypts its content
//------------------------------------------------------------------------
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

typedef struct
{
    char data;
    unsigned char nextElementAdress;
} block;
//------------------------------------------------------------------------
// FUNCTION: main
// PARAMETERS:
// argc --> argument count; argv --> arguments; argv[1] is the name of the file we want to decrypt
//------------------------------------------------------------------------
int main(int argc, char* argv[]){

    int fd;
    char character;
    block current;
    ssize_t read_value = 0, write_value = 0;
    if((fd = open(argv[1], O_RDONLY)) < 0){
        perror("open");
        return 1;
    }
    do{
        read_value = read(fd, &current.data, 1);
        if(read_value < 0){
            perror("read");
            return 1;
        }
        read_value = read(fd, &current.nextElementAdress, 1);
        if(read_value < 0){
            perror("read");
            return 1;
        }
        write_value = write(STDOUT_FILENO, &current.data, 1);
        if(write_value < 0){
            perror("write");
            return 1;
        }
        lseek(fd, current.nextElementAdress, SEEK_SET);
    }while(current.nextElementAdress != 0);
    return 0;
}
