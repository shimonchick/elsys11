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
#include <stdlib.h>

#define BUFFER_SIZE 500
#define FILENAME_SIZE 50
// PARAMETERS:
// const char* error --> the error message we want to print
// const char* variable --> the text of the variable we want to replace with %s
//------------------------------------------------------------------------
void print_error(const char* error, const char* variable);
// PARAMETERS:
// const char* filename --> the name of the file we want to execute the function on(used to print errors)
// int fd ---> file ddescriptor of the file we want to execute the function on
//------------------------------------------------------------------------
int tail(int fd, const char* filename){
    char character;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = 0, bytes_write = 0;

    off_t position;
    if((position = lseek(fd, -1 , SEEK_END)) < 0){
        perror("lseek");
        return 1;
    } 
    int lines = 0;
    while(lines < 11 && position != 0){ // there are 11 \n in 10 lines, including the one before the first line
        if((bytes_read = read(fd, &character, 1)) < 0){
            print_error("tail: error reading '%s': ", filename);
            perror("");
            
            return -1;
        }
        if(character == '\n'){
            lines++;
            if(lines == 11){ // so we don't seek back another byte after reading the last line
                break;
            }
        }
        if((position = lseek(fd, -2, SEEK_CUR)) < 0){
            perror("lseek");
            return -1;
        }
    } 
    bytes_read = 0;
    bytes_write = 0;
    while((bytes_read = read(fd, &character, 1)) != 0){
        if(bytes_read < 0){
            print_error( "tail: error reading '%s': ", filename);
            perror("");
            return -1;
        }
    
        while((bytes_write = write(STDOUT_FILENO, &character, 1)) != 1){
        
            if(bytes_write < 0){
                //print_error("tail: error writing '%s': ", filename);
                perror("tail: error writing 'standard output'");
                return -1;
            }

        }
    }
    return 0;
}
// PARAMETERS:
// int fd ---> the descriptor in which we want to write the read bytes from stdin
//------------------------------------------------------------------------

int read_stdin(int fd){
    ssize_t bytes_read, bytes_write;
    char character;
    while((bytes_read = read(STDIN_FILENO, &character, 1)) != 0){
        if(bytes_read < 0){
            perror("tail: error reading 'standard input': ");
            return -1;
        }
        while((bytes_write = write(fd, &character, 1)) != 1){
            if(bytes_write < 0){
                perror("tail: error writing 'standard output': ");
                return -1;
            }
        
        }
    }

    return 0;

}
// PARAMETERS:
// const char* name --> the name of the file, whose header we want to print
//------------------------------------------------------------------------

int print_header(const char* name, int newline){
    char filename_buffer[FILENAME_SIZE + 10] = "==> ";
    strcat(filename_buffer, name);
    strcat(filename_buffer, " <==\n");
    int size = strlen(filename_buffer);
    ssize_t bytes_write = 0;
    if(newline){
        while((bytes_write = write(STDOUT_FILENO, "\n", 1)) != 1){
            if(bytes_write < 0){
                perror("tail: error writing 'standard output': ");
                return -1;

            }
        }
    }
    int offset = 0;
    while(offset < size){
        bytes_write = write(STDOUT_FILENO, filename_buffer + offset, 1);
        if(bytes_write < 0){
            perror("tail: error writing 'standard output': ");
            return -1;
        }
        offset += 1;
    }
    return 0;
}
// creates a temporary file
//------------------------------------------------------------------------

int create_tmpfile(){
    char *filename = tmpnam(NULL);
    int fd;
    if ((fd = open(filename, O_CREAT | O_RDWR, 0744)) < 0) {
        return -1;
    }
    unlink(filename); 
    return fd;
}
// function details explained in declaration
void print_error(const char error[], const char variable[]){
    int size = strlen(error) + strlen(variable) - 2; // -2 for the %s  
    char* result = malloc(sizeof(char) * size);
    char* p;
    if((p = strstr(error, "%s"))){
        int error_index = 0;
        //printf("error: %s with size: %ld\n", error, strlen(error));
        //printf("variable: %s\n", variable);
        //printf("p: %c\n", *p);
        //printf("result size: %ld \n", strlen(result));
        for(; error[error_index] != *p; error_index++){
            //printf("error_index: %d\n", error_index);       
            result[error_index] = error[error_index];
        }
        int j = 0;
        for(;j < strlen(variable); j++){
            result[error_index + j] = variable[j];
        }
        for(int last = error_index + 2; last < strlen(error); last++){
            result[error_index + j] = error[last];
            error_index ++;
        }
        ssize_t bytes_write = 0;
        int offset = 0;
        while(offset < size){
            bytes_write = write(STDERR_FILENO, result + offset, 1);
            if(bytes_write < 0){
                perror("tail: error writing 'standard output': ");
            }
            offset += 1;
            
        }

    }
    free(result);
}
// PARAMETERS:
// const char* file_name --> the name of the file we want to execute the function on(used to print errors)
// int fd ---> file descriptor of the file we want to execute the function on
//------------------------------------------------------------------------

int open_file(int* fd, const char* file_name){
    if(strcmp(file_name, "standard input") == 0){
        if((*fd = create_tmpfile()) < 0){
            print_error("tail: cannot open '%s' for reading: ", file_name);
            perror("");
            return -1;
        } 
    }
    else{
        if((*fd = open(file_name, O_RDONLY)) < 0 ){
            print_error("tail: cannot open '%s' for reading: ", file_name);
            perror("");
            return -1;
        }
    }
    return 0;
}
// PARAMETERS:
// const char* file_name --> the name of the file we want to execute the function on(used to print errors)
// int fd ---> file ddescriptor of the file we want to execute the function on
//------------------------------------------------------------------------
int close_file(int fd, const char* file_name){
    if(close(fd) < 0){
       // print_error( "tail: error reading '%s': Input/output error", file_name);
        print_error( "tail: error reading '%s': ", file_name);
        
        perror("");
        return -1;    
    }
    return 0;
}

int main(int argc, char* argv[]){
    if( argc == 1 ){
        int fd;
        if((fd = create_tmpfile()) < 0){
            return 1;
        }
        if(read_stdin(fd) < 0){
            return 1;
        }
        if(tail(fd, "standard input") < 0){
            return 1;
        }
        if(close_file(fd, "standard input") < 0){
            return 1;
        }
        return 0;
    }
    for(int i = 1; i < argc; i++){ // rename "-" to "standard input" so we can use it when printing errors
        if((strcmp(argv[i], "-")) == 0){
            argv[i] = "standard input";
        }
    }
    if(argc == 2){
        int fd;
        if(open_file(&fd, argv[1]) < 0){
            return 1;
        }
        if(strcmp(argv[1], "standard input") == 0){
            if(read_stdin(fd) < 0){
                return 1;
            }
        }
        if(tail(fd, argv[1]) < 0){
            return 1;
        }
        if(close_file(fd, argv[1]) < 0){
            return 1;
        }
        return 0;
    }
    else{
        int is_first_header = 1;
        for(int i = 1; i < argc; i++){
            int fd;
            int newline;
            if(open_file(&fd, argv[i]) < 0){
                continue;
            }
            if(is_first_header){
                newline = 0;
                is_first_header = 0;
            }
            else{
                newline = 1;
            }
            if(print_header(argv[i], newline) < 0){
                continue;
            }
            if(strcmp(argv[i], "standard input") == 0){
                if(read_stdin(fd) < 0){
                    continue;
                }
            }
            if(tail(fd, argv[i]) < 0){
                continue;
            }
            if(close_file(fd, argv[i]) < 0){
                continue;
            }
        }
    }

    return 0;
}
