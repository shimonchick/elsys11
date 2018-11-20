#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define BUFFER_SIZE 256

int main(int argc, char* argv[]){
    char buffer[BUFFER_SIZE];
    int fd;
    ssize_t read_value = 0, write_value = 0;
    if((fd = open("a.txt", O_RDONLY)) < 0){
        perror("open");
        return -1;
    }
    lseek(fd, 5, SEEK_SET);
    read_value = read(fd, buffer, 10);
    if(read_value < 0){
        perror("read_value");
    }
    write_value = write(STDOUT_FILENO, buffer, 10);
    if(write_value < 0){
        perror("write_value");
    }
    return 0;
}
