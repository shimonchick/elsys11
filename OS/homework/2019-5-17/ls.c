#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <dirent.h>
#include <stdbool.h>
#include <getopt.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <errno.h>

bool is_showing_hidden = false;
bool is_verboose = false;
bool is_recursive = false;
bool is_size_printed = false;
int total = 0;

void print_filetype_letter(mode_t mode){
    char c;
    
    switch (mode & S_IFMT)
    {
        case S_IFBLK:
            c = 'b';
            break;
        case S_IFCHR:
            c = 'c';
            break;
        case S_IFDIR:
            c = 'd';
            break;
        case S_IFIFO:
            c = 'p';
            break;
        case S_IFLNK:
            c = 'l';
            break;
        case S_IFREG:
            c = '-';
            break;
        case S_IFSOCK:
            c = 's';
            break;
        default:
            c = '?';
            break;
    }
    printf("%c", c);
}
void print_permissions(mode_t mode){
    char permissions[9];

    permissions[0] =  (mode & S_IRUSR) ? 'r' : '-';
    permissions[1] =  (mode & S_IWUSR) ? 'w' : '-';
    permissions[2] =  (mode & S_IXUSR) ? 'x' : '-';
    permissions[3] =  (mode & S_IRGRP) ? 'r' : '-';
    permissions[4] =  (mode & S_IWGRP) ? 'w' : '-';
    permissions[5] =  (mode & S_IXGRP) ? 'x' : '-';
    permissions[6] =  (mode & S_IROTH) ? 'r' : '-';
    permissions[7] =  (mode & S_IWOTH) ? 'w' : '-';
    permissions[8] =  (mode & S_IXOTH) ? 'x' : '-'; 

    printf("%s", permissions);
}
void set_options(int argc, char* const argv[]){
    int opt;
    while((opt = getopt(argc, argv, "alR"))!= -1){
        switch(opt)
        {
            case 'a':
                is_showing_hidden = true;
                break;
            case 'l':
                is_verboose = true;
                break;
            case 'R':
                is_recursive = true;
                break;
            default:
                fprintf(stderr, "Usage: %s [-a] [-l] [-R] name\n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }
}

void print_file_information(const char* name){
    struct stat st;
    stat(name, &st); 
    print_filetype_letter(st.st_mode);
    if(is_verboose){
        print_permissions(st.st_mode);
        printf(" %ld", st.st_nlink);
       
        struct passwd* pwd;
        
        pwd = getpwuid(st.st_uid);
        printf(" %s", pwd->pw_name);
       
        struct group* gr;
        
        gr = getgrgid(st.st_gid);
        printf(" %s", gr->gr_name);

        printf("%5ld", st.st_size);
        
        struct tm tm_file, tm_now;
        localtime_r(&st.st_mtime, &tm_file);
        time_t now = time(NULL);
        localtime_r(&now, &tm_now);
        char time_str[64];
        if(tm_file.tm_year == tm_now.tm_year){
            strftime(time_str, sizeof(time_str), "%b %e %H:%M", &tm_file);
        }else{
            strftime(time_str, sizeof(time_str), "%b %e  %Y", &tm_file);    
        }
        printf(" %s", time_str);

    }
    char* last = strrchr(name, '/');
    if(last != NULL)
        printf(" %s\n", last + 1);
    else
        printf(" %s\n", name);
    //printf(" %s\n", name);
}
struct dirent* xreaddir(DIR* dir){
    struct dirent* entry;
    entry = readdir(dir);
    if(errno != 0 && entry == NULL){
        perror("readdir");
        exit(1);
        //return NULL;
    }
    return entry;
}
DIR* xopendir(const char* path){
    DIR* dir = opendir(path);
    if(dir == NULL && errno != 0){
        perror("opendir");
        exit(1);
    }
    return dir;
}
long dir_size(const char* path){
    long size = 0;
    printf("trying to open directory: %s\n", path);
    DIR* dir = xopendir(path);
    struct dirent* entry;
    while((entry = xreaddir(dir))){
        struct stat st;
        stat(entry->d_name, &st);
        if(S_ISDIR(st.st_mode)){ // recursively call for directories
            if( !strcmp( ".", entry->d_name ) || !strcmp( "..", entry->d_name ) )
                continue;
            
            char* dir_name = malloc(sizeof(char) * strlen(path) + sizeof(char) * strlen(entry->d_name) + 2);
            strcpy(dir_name, path);
            strcat(dir_name, "/");
            strcat(dir_name, entry->d_name);

            size += dir_size(dir_name);
            free(dir_name);
        }else{ // file
            size += st.st_size;
        }
    }
}
void print_directory(const char* path){
    DIR *dir = xopendir(path);
    struct dirent *entry;
    int capacity = 2;
    int size = 0;
    char (*recursive_dir_names)[4096] = malloc(sizeof(char) * 4096 * capacity);
    while((entry = xreaddir(dir))) {
        if(entry->d_name[0] == '.' && !is_showing_hidden){
            continue;
        }
        char dir_name[4096]; // max path size in unix 
        strcpy(dir_name, path);
        strcat(dir_name, "/");
        strcat(dir_name, entry->d_name);
       
        if(entry->d_type == DT_DIR && is_recursive){
            if(size == capacity){
                capacity *= 2;
                recursive_dir_names = realloc(recursive_dir_names, capacity * sizeof(char) * 4096);
            }
            strcpy(recursive_dir_names[size],dir_name);
            size++;
        }
        else{
            print_file_information(dir_name);
        }
    }
    for(int i = 0; i < size; i++){
        printf("%s:\n", recursive_dir_names[i]);
        print_directory(recursive_dir_names[i]);

    }
    free(recursive_dir_names);

    closedir(dir);
}
int main(int argc, char* argv[]){
    
    set_options(argc, argv);
    if(argc == optind){
        print_directory(".");
    }
    else{
        for(int i = 1; i < argc; i++){
            if(argv[i][0] == '-'){ // skip arguments
                continue;
            }
            struct stat st;
            stat(argv[i], &st);
            if((st.st_mode & S_IFMT)== S_IFDIR){
                if(is_verboose && !is_size_printed){
                    printf("total %ld", dir_size(argv[i]));
                    is_size_printed = true;
                }
                if(argc > 2){
                    if(i > 1){
                        printf("\n");
                    }
                    printf("%s:\n", argv[i]);
                }
                print_directory(argv[i]);
            }else {
                print_file_information(argv[i]);
            }
        }

    }
    return 0;
}
