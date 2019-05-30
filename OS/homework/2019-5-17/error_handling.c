#include "error_handling.h"
#include <stdbool.h>
bool xstat(const char* pathname, struct stat* statbuf){
    if(stat(pathname, statbuf) != 0){
        if(errno == EACCES){
            fprintf(stderr, "ls: cannot open directory %s", pathname);
            perror("");
        }
        else if(errno == ENOENT){
            fprintf(stderr, "ls: cannot access %s: ", pathname);
            perror("");
        }
        else{
            perror("stat");

        }
        return false;
    }
    return true;

}

struct dirent* xreaddir(DIR* dir){
    struct dirent* entry;
    entry = readdir(dir);
    if(errno != 0 && entry == NULL){
        perror("readdir");
        exit(1);
    }
    return entry;
}
DIR* xopendir(const char* path){
    DIR* dir;
    if((dir = opendir(path)) == NULL && errno != 0){
        if(errno == EACCES){
            fprintf(stderr, "ls: cannot open %s: ", path);
            perror("");
        }
        else{
            perror("opendir");
        }
    }
    return dir;
}
void xclosedir(DIR* dir){
    if(closedir(dir)!= 0){
        perror("closedir");
        exit(1);
    }
}
