#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_WORDS 100
#define WORD_SIZE 200
#define LINE_SIZE MAX_WORDS * WORD_SIZE
// result should be freed manually
char** parse_cmdline(char* line){
    char** result;
    result = malloc(sizeof(char*) * MAX_WORDS);
    int i = 0;
    char* p = strtok(line, " ");
    while(p != NULL){
        result[i] = malloc(sizeof(char) * WORD_SIZE);
        result[i] = p;
        printf("word:%s\n", result[i]);
        i++;
        p = strtok(NULL, " ");
    }
    return result;

}

int main(int argc, char* argv[]){
    while(1){

        char* line;
        size_t length = 0;
        getline(&line, &length, stdin); // dinamically alocates line;
        printf("line: %s", line);
        char** words = parse_cmdline(line);
        for(int i = 0; i < MAX_WORDS; i++){
            printf("%s ", words[i]);
        }
        pid_t pid = fork();
        if(pid < 0){
            perror("fork");
            return 1;
        }
        if(pid == 0){ // child
            execv(words[0], &words[0]);
        }
        else{
            int status;
            if((status = waitpid(pid, &status, 0)) < 0){
                perror("waitpid");
                return 1;
            }
        }
        for(int i = 0; i < MAX_WORDS; i++){
            free(words[i]);
        }
      free(line);

    }
    return 0;
}
