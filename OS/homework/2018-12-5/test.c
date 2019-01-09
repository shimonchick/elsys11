#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define LINE_SIZE 500
// result should be freed manually
char** parse_cmdline(char* line){
    char** result = malloc(sizeof(char*) * 1);
    int i = 0;
    int capacity = 1;
    char* p = strtok(line, " ");
    while(p != NULL){
        if(i == capacity){
            capacity *= 2;
            result = realloc(result, sizeof(char*) * capacity);
        }
        result[i] = p;
        //printf("word:%s ", result[i]);
        i++;
        p = strtok(NULL, " ");
    }
    if(capacity == i){
        capacity *= 2;
        result = realloc(result, sizeof(char*) * capacity);
    }
    result[i] = NULL;
    return result;

}

int main(int argc, char* argv[]){
    while(1){
        printf("$ ");
        char* line = malloc(sizeof(char) * LINE_SIZE);
        size_t length = 0;
        while(getline(&line, &length, stdin) == -1){
            free(line);
        } // dinamically alocates line;
        
        //if(feof(stdin)){
        //    break;
        //}
        line[strlen(line) - 1] = '\0'; // eliminating the new line at the end
        free(line);
    //    //printf("line:%s with size:%d\n", line, strlen(line));
    //    char** words = parse_cmdline(line);
    //   // for(int i = 0; i < MAX_WORDS; i++){
    //   //     printf("%s ", words[i]);
    //   // }
    //    pid_t pid = fork();
    //    if(pid < 0){
    //        perror("fork");
    //        return 1;
    //    }
    //    //printf("words[0]:%s", words[0]);
    //    if(pid == 0){ // child
    //        //printf("child process\n");
    //        //char* arr[] = {"ls", "-a ", "-l"};
    //        //char* command[3];
    //        //command[0] = "/bin/ls";
    //        //command[1] = "-al";
    //        //command[2] = NULL;
    //        if(execvp(words[0], words) < 0){
    //            fprintf(stderr, "%s: ", words[0]);
    //            perror("");
    //            
    //            for(int i = 0; words[i] != NULL; i++) {
    //                free(words[i]);
    //            }
	//	        free(words);
    //            free(line);
    //            return 1;
    //        }
    //        //don't know if i should free after successful exec
    //        //for(int i = 0; words[i] != NULL; i++) {
    //        //    free(words[i]);
    //        //}
    //        //free(words);
    //        //free(line);
    //        return 0;
    //    }else{
    //        int status;
    //        if(waitpid(pid, &status, 0) < 0){
    //            perror("waitpid");
    //            return 1;
    //        }
    //        //printf("parent process\n");w
    //        //for(int i = 0; words[i] != NULL; i++) {
    //        //    free(words[i]);
    //        //}
    //        free(words);
    //        free(line);
    //    }

    }
    return 0;
}
