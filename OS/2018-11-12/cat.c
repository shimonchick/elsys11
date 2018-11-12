#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define BUFFER_SIZE 1000000

int main(int argc, char* argv[]){
    char buffer[BUFFER_SIZE];
    int fd;
    if((fd = open(argv[1], O_RDONLY)) < 0){
        perror("open");
        return 1;
    }

    ssize_t bytes_read, bytes_write;
    int bytes_remaining;
    char* write_pos;
    while((bytes_read = read(fd, buffer, BUFFER_SIZE)) != 0){
        if(bytes_read < 0){
            perror("read");
            return 1;
        }
        bytes_remaining = bytes_read;
        write_pos = buffer;
        while((bytes_write = write(STDOUT_FILENO, write_pos, bytes_remaining)) != 0){
            if(bytes_write < 0){
                perror("write");
                return 1;
            }

            bytes_remaining -= bytes_write; 
            write_pos += bytes_write;
        
        }
    }


}
