#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdbool.h>
#include <getopt.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include "error_handling.h"


bool is_showing_hidden = false;
bool is_verboose = false;
bool is_recursive = false;
bool is_size_printed = false;

//--------------------------------------------
// FUNCTION: print_filetype_letter
// prints a letter that corresponds with the type of a file
// PARAMETERS:
// mode -> bit mask containing file type
//----------------------------------------------
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
//--------------------------------------------
// FUNCTION: print_permissions
// prints the permissions for a file
// PARAMETERS:
// mode -> bitmap containing the file permissions
//----------------------------------------------
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
//--------------------------------------------
// FUNCTION: set_options
// reads the options from the argument vector and sets the appropriate flags 
// PARAMETERS:
// argc -> argument count; argv -> argument vector
//----------------------------------------------
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

//--------------------------------------------
// FUNCTION: print_file_information
// prints information about a file
// PARAMETERS:
// path -> path to file
//----------------------------------------------
void print_file_information(const char* path){
    struct stat st;
    if(!xstat(path, &st)) return; 
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
    char* last = strrchr(path, '/');
    if(last != NULL)
        printf(" %s\n", last + 1);
    else
        printf(" %s\n", path);
}
//--------------------------------------------
// FUNCTION: dir_size
// get the size of a directory
// PARAMETERS:
// path -> path to the directory
//----------------------------------------------
int dir_size(const char* path){
    int size = 0;
    DIR* dir = xopendir(path);
    struct dirent* entry;
    while((entry = xreaddir(dir))){
        struct stat st;
        stat(entry->d_name, &st);
        size += st.st_size;
    }
    xclosedir(dir);
    return size;
}
//--------------------------------------------
// FUNCTION: print_directory
// prints the contents of a directory
// PARAMETERS:
// path -> path to the directory
//----------------------------------------------
void print_directory(const char* path){
    DIR *dir = xopendir(path);
    if(dir == NULL) return;
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
       
        if(entry->d_type == DT_DIR && is_recursive && entry->d_name[0]!='.'){
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
    if(is_recursive){
        for(int i = 0; i < size; i++){
            printf("\n%s:\n", recursive_dir_names[i]);
            print_directory(recursive_dir_names[i]);
        }

    }
    free(recursive_dir_names);

    xclosedir(dir);
}
int main(int argc, char* argv[]){
    set_options(argc, argv);
    if(argc == optind){
        struct stat st;
        if(!xstat(".", &st)) exit(1);
        if(is_recursive){
            printf(".:\n");
        }
        print_directory(".");
    }
    else{
        for(int i = 1; i < argc; i++){
            if(argv[i][0] == '-'){ // skip arguments
                continue;
            }
            struct stat st;
            if(!xstat(argv[i], &st)) continue;

            if((st.st_mode & S_IFMT)== S_IFDIR){
                if(is_verboose && !is_size_printed){
                    printf("total %d", dir_size(argv[i]));
                    is_size_printed = true;
                }
                if(argc > 2){
                    printf("%s:\n", argv[i]);

                }
                print_directory(argv[i]);
                if(argc > 2 && i != argc - 1){
                    printf("\n");

                }
            }else {
                print_file_information(argv[i]);
            }
        }

    }
    return 0;
}
