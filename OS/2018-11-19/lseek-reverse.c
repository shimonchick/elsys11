
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
    if((fd_write = open("a.txt", O_WRONLY) < 0)){
        perror("open");
        return 1;
    }
    block current;
    int block_count = 1;
    off_t seek_position, end_position;
    ssize_t read_value = 0, write_value = 0;
    if((seek_position = lseek(fd_read, 0, SEEK_END)) < 0){
        perror("lseek");
    }
    end_position = lseek(fd_read, -1, SEEK_CUR);
    if((read_value = read(fd_read, &current.data, 1)) < 0){
        perror("read");
    }
    current.nextElementAdress = 0;
    if((write_value = write(fd_write, &current.data, 1)) < 0){
        perror("write");
    }
    if((write_value = write(fd_write, &current.nextElementAdress, 1)) < 0){
        perror("write");
    }
    
    
    if((seek_position = lseek(fd_read, 0, SEEK_SET)) < 0){
        perror("lseek");
    }

    while((seek_position = lseek(fd_read, 1, SEEK_CUR)) != end_position){
        if((read_value = read(fd_read, &current.data, 1)) < 0){
            perror("read");
        }
        current.nextElementAdress = seek_position * 2;
        if((write_value = write(fd_write, &current.data, 1)) < 0){
            perror("write");
        }
        if((write_value = write(fd_write, &current.nextElementAdress, 1)) < 0){
            perror("write");
        }    
    }


    
    return 0;
}
