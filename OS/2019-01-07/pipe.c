#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
//    int new_fd_requested = 3;
//    int new_fd;
//    if((new_fd = dup2(STDOUT_FILENO, new_fd_requested)) < 0){
//        perror("dup2");
//        exit(1);
//    }
//
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
        dup2(fdpipe[1], STDOUT_FILENO);
        close(fdpipe[0]);
        close(fdpipe[1]);
        if(execlp("ls", "ls") < 0){ 
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
  //  int pipefd[2] = {new_fd, STDIN_FILENO};
  //  if(pipe(pipefd) < 0){
  //      perror("pipe");
  //      exit(1);
  //  }
    pid_t pid2 = fork();
    if(pid2 < 0){
        perror("fork");
        exit(1);
    }
    else if(pid2 == 0){
        close(STDIN_FILENO);
        dup2(fdpipe[0], STDIN_FILENO);
        if(execlp("wc", "wc") < 0){
            perror("wc");
            exit(1);
        }
    }
    else{
        int rstatus;
        if(waitpid(pid, &rstatus, 0) < 0){
            perror("waitpid");
            exit(1);
        }


    }

    

    exit(0);
}

