//------------------------------------------------------------------------
// NAME: Mihail Kirov
// CLASS: XIb
// NUMBER: 19
// PROBLEM: #1
// FILE NAME: tail.c
// FILE PURPOSE:
// prints the last 10 lines of a file
//------------------------------------------------------------------------
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 5
#define FILENAME_SIZE 50
// PARAMETERS:
// const char* filename --> the name of the file we want to execute the function on
//------------------------------------------------------------------------
int tail(const char* filename){
    
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = 0;
    if((fd = open(filename, O_RDONLY)) < 0){
        perror("open");
        return 1;
    }
    if(lseek(fd, 0, SEEK_END) < 0){
        perror("lseek");
        return 1;
    } 
    int lines = 0, total_offset = BUFFER_SIZE;
    if(lseek(fd, -total_offset, SEEK_CUR) < 0){
        perror("lseek");
        return 1;
    }
    while((bytes_read = read(fd, buffer, BUFFER_SIZE)) != 0){
        if(bytes_read < 0){
            perror("read");
            return 1;
        }
        int i = bytes_read - 1;
        while(i > 0 && lines != 10){
            if(buffer[i--] == '\n'){
                lines++;
            }
        }
        if(lines == 10){
            if(lseek(fd, -bytes_read, SEEK_CUR) < 0){
                perror("lseek");
                return 1;
            }
            ssize_t bytes_read = 0;
            while((bytes_read = read(fd, buffer, BUFFER_SIZE)) != 0){
                if(bytes_read < 0){
                    perror("read");
                    return 1;
                }
                write(fd, buffer, bytes_read);
            } 

            break;
        
        }
        total_offset += bytes_read;
        if(lseek(fd, -total_offset, SEEK_CUR) < 0){
            perror("lseek");
            return 1;
        }
        

    }

}

int main(int argc, char* argv[]){
    if(argc == 1){
        return 1;
    }
    else if(argc == 2){
        tail(argv[1]);
    }
    else{
        for(int i = 1; i < argc; i++){
            char filename_buffer[FILENAME_SIZE + 10] = "==> ";
            strcat(filename_buffer, argv[i]);
            strcat(filename_buffer, " <==\n");
            write(STDOUT_FILENO, filename_buffer, strlen(filename_buffer));
            tail(argv[i]);
            if(i != argc - 1){
                write(STDOUT_FILENO, "\n", 1);
            }
        }
    }
        
    return 0;
}
