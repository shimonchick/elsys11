#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>

#define true 1

int main(){
    char* fifo = "tmp/fifo";
    
    int fd = open(fifo, O_RDONLY);
    char arr[80];
    while(true){
        read(fd, arr, sizeof(arr));

        printf("User2: %s\n", arr);
        
        close(fd);



    }
    exit(0);
}
