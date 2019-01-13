#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define READ_END 0
#define WRITE_END 1
int main(int argc, char* argv[])
{
    int fdpipe[2];
    if(pipe(fdpipe) < 0){
        perror("pipe");
        exit(1);
    }
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        exit(1);
    }
    else if(pid == 0){
        close(STDOUT_FILENO); 
        dup2(fdpipe[WRITE_END], STDOUT_FILENO);
        close(fdpipe[READ_END]);
        close(fdpipe[WRITE_END]);
        char* arg[2] = {"ls", NULL};
        if(execvp("ls", arg) < 0){ 
            perror("execl");
            exit(1);
        } 
    } else{
        int rstatus;
        if(waitpid(pid, &rstatus, 0) < 0){
            perror("waitpid");
            exit(1);
        }


    }
    
    pid_t pid2 = fork();
    if(pid2 < 0){
        perror("fork");
        exit(1);
    }
    else if(pid2 == 0){
        close(STDIN_FILENO);
        dup2(fdpipe[READ_END], STDIN_FILENO);
        close(fdpipe[READ_END]);
        close(fdpipe[WRITE_END]);

        char* arg[2] = {"wc", NULL};
        if(execvp("wc", arg) < 0){
            perror("wc");
            exit(1);
        }
    }
    else{
        int rstatus;
        close(fdpipe[READ_END]);
        close(fdpipe[WRITE_END]);
        if(waitpid(pid2, &rstatus, 0) < 0){
            perror("waitpid");
            exit(1);
        }


    }

    

    exit(0);
}

