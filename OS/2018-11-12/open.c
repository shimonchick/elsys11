#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 100
int main(){

    char buf[BUFFER_SIZE];
    int fd = open("a.txt", O_APPEND);
    if(fd < 0){
        perror("open");
        return 1;
    }
    ssize_t read_value, write_value;

    while((read_value = read(fd, buf, BUFFER_SIZE /*- 1*/)) != 0){
        if(read_value < 0)
        {
            perror("read");
            return 1;
        }
        buf[read_value] = '\0';
        printf("%s", buf);
        while((write_value = write(STDOUT_FILENO, buf, read_value))!= 0)
        {
            if(write_value < 0)
            {
                perror("write");
                return 1;
            }
        }
    
    }
    if(close(fd) < 0){
        perror("close");
        return 1;
    }
    return 0;
}
