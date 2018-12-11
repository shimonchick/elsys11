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
char** parse_cmdline(const char* line){
    char** result; 
    result = malloc(sizeof(char*) * MAX_WORDS);
    int size = MAX_WORDS;
    for(int i = 0; i < size; i++){
        result[i] = malloc(sizeof(char) * WORD_SIZE);
    }
    char c;
    int word_count = 0;
    while(( c = getc(stdin)) != '\n'){
        ungetc(c, stdin);
        char word[WORD_SIZE];
        scanf("%s", word);
        strcpy(result[word_count], word);
        printf("word read: %s", word);
    }
    return result;

}

int main(int argc, char* argv[]){
    while(1){

        char line[LINE_SIZE];
        getline(line, 0, stdin); // dinamically alocates line;
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
        free(words);

    }
    return 0;
}
