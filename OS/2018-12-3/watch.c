#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char* argv[]){
    while(1){
        pid_t pid = fork();
        if(pid < 0){
            perror("fork");
            sleep(2);
            continue;
        }
        else if( pid == 0 ){ // child process
            //char buffer[100];
            //strcat(buffer, "/bin/");
            //strcat(buffer, argv[1]);
            //printf("%s\n", buffer);
            if(execv(argv[1], &argv[1]) < 0){
                fprintf(stderr, "%s: ", argv[1]);
                perror("");
                return 1;
            }

            
        }
        else{ // parent process
           int rstatus;
            if(waitpid(pid, &rstatus, 0) < 0){
                perror("waitpid");
                return 1;
            }

        }
        sleep(2);

    }

    return 0;

}

