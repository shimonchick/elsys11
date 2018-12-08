#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){

    printf("Hello before fork\n");
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        return -1;
    }
    else if( pid == 0 ){
        printf("Hello after fork from child process\n");
        if(execl("/bin/ls", "/bin/ls", "-l", NULL) < 0){
            perror("execl");
            return -1;
        }

        
    }
    else{
       int rstatus;
        printf("Hello after fork from parent process (child pid %d)\n", pid);
        if(waitpid(pid, &rstatus, 0) < 0){
            perror(waitpid);
            return -1;
        }
        printf("Waiting for child %d with return status %d\n", pid, WEXITSTATUS(rstatus));


    }


    return 0;

}
