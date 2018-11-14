#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    char character;
    int fd;
    if((fd = open("a.txt", O_RDONLY)) < 0)
    {
        perror("open");
        return 1;
    }

    int lines = 0;
    while(lines < 10){
        
        read(fd, &character, 1);
        write(STDOUT_FILENO, &character, 1);
        if(character == '\n'){
            lines++;
        }
    }


    return 0;
}
