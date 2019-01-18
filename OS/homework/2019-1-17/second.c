
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h> 
#include <stdlib.h>

#define true 1

void write_fifo(const char* fifo){
    int fd = open(fifo, O_WRONLY);
    if(fd < 0){
        perror("open");
        exit(1);
    }
    char arr[100];
    if(fgets(arr, 100, stdin) == 0){
        //printf("no input");
        //close(fifo);
        exit(0);
    } 
    write(fd, arr, strlen(arr) + 1);
    close(fd);
}
void read_fifo(const char* fifo){
    int fd = open(fifo, O_RDONLY);
    if(fd < 0){
        perror("open");
        exit(1);
    }
    char arr[100];
    ssize_t bytes_read = read(fd, arr, sizeof(arr));
    printf("User1: %s", arr);

}
int main(){
    char* fifo = "chat";
    char* fifo2 = "chat2";
    mkfifo(fifo2, 0666);
    while(true){
        pid_t pid = fork();
        if(pid < 0){
            perror("fork");
            exit(1);

        }
        pid_t pid2 = fork();
        if(pid2 < 0){
            perror("fork");
            exit(1);
        }
        
        if( pid == 0 ){
            read_fifo(fifo);
        }
        if(pid2 == 0){
            write_fifo(fifo2);

        }

        else{
            int status, status2;
            waitpid(pid, &status, 0);
            waitpid(pid2, &status2, 0);

        }

        
    }
    
    exit(0);
}
