
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

int main(int argc, char* argv[]){
    int fd_read, fd_write;
    if((fd_read = open(argv[1], O_RDONLY)) < 0){
        perror("open");
        return 1;
    }
    if((fd_write = open("a.txt", O_WRONLY)) < 0){
        perror("open");
        return 1;
    }
    char character;
    block previous;
    int block_count = 1;
    read(fd_read, &previous.data, 1);
    //previous.nextElementAdress = block_count * 2;
    //block_count++;
    write(fd_write, &previous.data, 1);
    //write(fd_write, &previous.nextElementAdress);
    ssize_t bytes_read = 0;
    do{
        bytes_read = read(fd_read, &character, 1);
        if(bytes_read == 0){
            previous.nextElementAdress = 0;
            write(fd_write, &previous.nextElementAdress, 1);
            break;
        }
        else{
            previous.nextElementAdress = block_count * 2;
            block_count ++;
            write(fd_write, &previous.nextElementAdress, 1);
            write(fd_write, &character, 1);
            previous.data = character;
        }

    }while(bytes_read != 0);

    close(fd_read);
    close(fd_write);
    
    return 0;
}
