#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define true 1

int main(){
    char* pathname = "/tmp/fifo";
    mkfifo(pathname, 0666);
    char arr[80];
    while(true){
        int fd = open(pathname, O_WRONLY);

        fgets(arr, 80, stdin);

        write(fd, arr, strlen(arr)+1);
        write(STDOUT_FILENO, arr, strlen(arr)+1);
        close(fd);
    }
    exit(0);
}
