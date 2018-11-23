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
int tail(int fd){
    char character;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = 0;

    off_t position;
    if((position = lseek(fd, -1 , SEEK_END)) < 0){
        perror("lseek");
        return 1;
    } 
    int lines = 0;
    while(lines < 11 && position != 0){ // there are 11 \n in 10 lines, including the one before the first line
        if((bytes_read = read(fd, &character, 1)) < 0){
            perror("read");
            return 1;
        }
        if(character == '\n'){
            lines++;
            if(lines == 11){ // so we don't seek back another byte after reading the last line
                break;
            }
        }
        if((position = lseek(fd, -2, SEEK_CUR)) < 0){
            perror("lseek");
            return 1;
        }
    } 
    while((bytes_read = read(fd, buffer, BUFFER_SIZE)) != 0){
        if(bytes_read < 0){
            perror("read");
            return 1;
        }
        write(STDOUT_FILENO, buffer, bytes_read);
    }
}
int read_stdin(int fd){
    ssize_t bytes_read, bytes_write;
    char buffer[BUFFER_SIZE];
    while((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) != 0){
        if(bytes_read < 0){
            perror("read");
            return -1;
        }
        bytes_write = write(fd, buffer, bytes_read);
        if(bytes_write < 0){
            perror("write");
            return -1;
        }
    
    }

    return fd;
}
int main(int argc, char* argv[]){
    if(argc == 1){ // STDIN
        char *filename = tmpnam(NULL);
        int fd;
        if ((fd = open(filename, O_CREAT | O_RDWR, 0744)) < 0) {
            perror("error with open for tmpnam");
            return 1;
        }
        unlink(filename); 
        read_stdin(fd);
        tail(fd);
        close(fd);
    }
    else if(argc == 2){ // 1 file
        int fd;
        if((fd = open(argv[1], O_RDONLY)) < 0 ){
            perror("open");
            return 1;
        }
        tail(fd);
        close(fd);
    }
    else{ // multiple files
        for(int i = 1; i < argc; i++){
            char filename_buffer[FILENAME_SIZE + 10] = "==> ";
            strcat(filename_buffer, argv[i]);
            strcat(filename_buffer, " <==\n");
            write(STDOUT_FILENO, filename_buffer, strlen(filename_buffer));

            int fd;
            if((fd = open(argv[i], O_RDONLY)) < 0 ){
                perror("open");
                return 1;
            }
            tail(fd);
            close(fd);

            if(i != argc - 1){
                write(STDOUT_FILENO, "\n", 1);
            }
        }
    }

    return 0;
}
