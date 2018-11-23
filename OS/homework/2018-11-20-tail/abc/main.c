#include <unistd.h> 
#include <stdlib.h>
int main(int argc, char ** argv) {
    argv[0] = "/usr/bin/tail";
    execv("/usr/bin/tail", argv);
}
