#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define BUFFER_SIZE 1

int main(int argc, char* argv[]){
    char buffer[BUFFER_SIZE];
    int fd;
    if((fd = open("a.txt", O_RDONLY)) < 0){
        perror("open");
        return 1;
    }

    ssize_t bytes_read, bytes_write;
    int bytes_remaining;
    char* write_pos;
    int lines = 0;
    while(lines < 10){
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
                
                write_pos += bytes_write;
                bytes_remaining -= bytes_write;
            
            }
            if(buffer[0] == '\n'){
                printf("lines++");
                lines++;
            }
        }
    }
}
