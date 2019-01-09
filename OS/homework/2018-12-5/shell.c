//--------------------------------------------
// NAME: Mihail Kirov
// CLASS: XIb
// NUMBER: 19
// PROBLEM: #1
// FILE NAME: shell.c
// FILE PURPOSE:
// simple implementation of a shell program
// ...
//---------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
//--------------------------------------------
// FUNCTION: char** parse_cmdline(char* line)
// parses a line and returns a dinamically allocated array of 
// pointers to null terminated c-strings 
// PARAMETERS:
// char* line --> null-terminated line that should be parsed
// NOTE: result should be freed manually
//----------------------------------------------
char** parse_cmdline(char* line){
    char** result = malloc(sizeof(char*) * 1);
    int i = 0;
    int capacity = 1;
    char* p = strtok(line, " ");
    while(p != NULL){
        if(i == capacity ){
            capacity *= 2;
            result = realloc(result, sizeof(char*) * capacity);
        }
        result[i] = p;
        //printf("word:%s ", result[i]);
        i++;
        p = strtok(NULL, " ");
    }
    if(i == capacity ){
        capacity += 1;
        result = realloc(result, sizeof(char*) * capacity);
    }
    result[i] = NULL;
    return result;

}
//--------------------------------------------
// FUNCTION: char* read_line()
// reads a line from standard input, stores it in dynamically allocated
// memory and returns it. The function returns the line including a newline and terminating byte.
//----------------------------------------------
char* read_line(){
    char* result = malloc(sizeof(char) * 100); // default
    char character;
    int size = 0;
    int capacity = 100;
    do{
        if(size == capacity ){
            capacity *= 2;
            result = realloc(result, sizeof(char) * capacity);
        }
        ssize_t bytes_read;
        while((bytes_read = read(STDIN_FILENO, &character, 1)) != 1){
            if(bytes_read == 0){
                free(result);
                exit(0);
            }
            if(bytes_read < 0){
                perror("read");
                exit(1);
            }
        }
        result[size] = character;
        size++;

    }while(character != '\n');
    if(size == capacity ){
        capacity += 1;
        result = realloc(result, sizeof(char) * capacity);
    }
    result[size] = '\0';
    return result;
}
//--------------------------------------------
// FUNCTION: void write_starting_symbols()
// writes the starting sequence of the shell ---> "$ "
//----------------------------------------------
void write_starting_symbols(){
    ssize_t bytes_write;
    char* sequence = "$ ";
    int total = 0;
    while((bytes_write = write(STDOUT_FILENO, sequence + total, strlen(sequence) - total))  != 0){
        if(bytes_write < 0){
            perror("write");
            exit(1);
        }
        total += bytes_write;
    }
}
//--------------------------------------------
// FUNCTION: int main(int argc, char* argv[])
// creates a new process that executes the command given as input
//----------------------------------------------
int main(int argc, char* argv[]){
    while(1){
        write_starting_symbols();
        char* line = read_line();
        line[strlen(line) - 1] = '\0'; // eliminating the new line at the end
        //printf("line:%s with size:%d\n", line, strlen(line));
        char** words = parse_cmdline(line);
        pid_t pid = fork();
        if(pid < 0){
            perror("fork");
            free(line);
            free(words);
            continue;
        }
        if(pid == 0){ // child
            //printf("child process\n");
            //char* arr[] = {"ls", "-a ", "-l"};
            //char* command[3];
            //command[0] = "/bin/ls";
            //command[1] = "-al";
            //command[2] = NULL;
            if(execvp(words[0], words) < 0){
                fprintf(stderr, "%s: ", words[0]);
                perror("");
                
	            free(words);
                free(line);
                return 1;
            }
            //for(int i = 0; words[i] != NULL; i++) {
            //    free(words[i]);
            //}
            free(words);
            free(line);
            return 0;
        }else{
            int status;
            if(waitpid(pid, &status, 0) < 0){
                perror("waitpid");
                return 1;
            }
            //printf("parent process\n");w
            //for(int i = 0; words[i] != NULL; i++) {
            //    free(words[i]);
            //}
            free(words);
            
            free(line);
        }

    }
    return 0;
}
