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

#define max(a,b) \
({ __typeof__ (a) _a = (a); \
   __typeof__ (b) _b = (b); \
 _a > _b ? _a : _b; })

bool is_showing_hidden = false;
bool is_verboose = false;
bool is_recursive = false;


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
//void print_filetype_letter(mode_t mode)
//{
//    char c;
//
//    if (S_ISREG(mode))
//        c = '-';
//    else if (S_ISDIR(mode))
//        c = 'd';
//    else if (S_ISBLK(mode))
//        c = 'b';
//    else if (S_ISCHR(mode))
//        c = 'c';
//#ifdef S_ISFIFO
//    else if (S_ISFIFO(mode))
//        c = 'p';
//#endif  /* S_ISFIFO */
//
//#ifdef S_ISLNK
//    else if (S_ISLNK(mode))
//        c = 'l';
//#endif  /* S_ISLNK */
//
//#ifdef S_ISSOCK
//    else if (S_ISSOCK(mode))
//        c = 's';
//#endif  /* S_ISSOCK */
//
//#ifdef S_ISDOOR
//    else if (S_ISDOOR(mode))
//        c = 'D';
//#endif 
//    else
//        c = '?';
//    
//    printf("%c",c);
//}
//void print_filetype_letter(struct dirent* entry){
//    char c;
//    switch(entry->d_type){
//        case DT_BLK:
//            c = 'b';
//            break;
//        case DT_CHR:
//            c = 'b';
//            break;
//        case DT_DIR:
//            c = 'd'
//            break;
//        case DT_FIFO:
//            c = 'p';
//            break;
//        case DT_LNK:
//            c = 'l';
//            break;
//        case DT_REG:
//            c = '-';
//            break;
//        case DT_SOCK:
//            c = 's';
//            break;
//        case DT_UNKNOWN:
//            c = '?';
//            break;
//        default:
//            printf("Unsupported file type");
//            exit(1);
//    }
//    pritnf("%c", c);
//}
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
    //if(optind >= argc){
    //    fprintf(stderr, "Expected argument after options\n");
    //}
    printf("is_showing_hidden: %d, is_veboose: %d, is_recursive:%d\n", is_showing_hidden, is_verboose, is_recursive);
}

void print_file_information(const char* name){
    struct stat st;
    //printf("file name: %s\n", name);
    stat(name, &st); 
    print_filetype_letter(st.st_mode);
    if(is_verboose){
        print_permissions(st.st_mode);
        printf("%3ld", st.st_nlink);
       
        struct passwd* pwd;
        
        pwd = getpwuid(st.st_uid);
        printf("%s ", pwd->pw_name);
       
        struct group* gr;
        
        gr = getgrgid(st.st_gid);
        printf("%s", gr->gr_name);

        printf("%10ld", st.st_size);
        
        struct tm* tm;
        tm = localtime(&st.st_atime);
        printf("%s", asctime(tm));
    }
    printf(" %s\n", name);
}

void print_directory(const char* name){
    DIR *dir = opendir(name);
    //TODO: error check opendir
    struct dirent *entry;
    if(is_recursive){
        printf("%s:\n", name);
    }
    while((entry = readdir(dir))) {
        if(entry->d_name[0] == '.' && !is_showing_hidden){
            continue;
        }
        if(entry->d_type == DT_DIR && is_recursive){
            printf("%s/%s:\n", name, entry->d_name);
            char* dir_name = malloc(sizeof(char) * strlen(name) + sizeof(char) * strlen(entry->d_name) + 2);
            strcpy(dir_name, name);
            strcat(dir_name, "/");
            strcat(dir_name, entry->d_name);
            printf("printing directory: %s\n", dir_name);
            print_directory(dir_name);
        }
        else{
            print_file_information(entry->d_name);
        }
    }

    closedir(dir);
}

int main(int argc, char* argv[]){
    
    set_options(argc, argv);
    if(argc == 1){
        argv[1] = malloc(sizeof(char) * 2);
        argv[1] = ".";
    }
    for(int i = 1; i < max(argc, 2); i++){
        if(argv[i][0] == '-'){ // skip arguments
            continue;
        }
        struct stat st;
        stat(argv[i], &st);
        if(S_ISDIR(st.st_mode)){
            print_directory(argv[i]);
        }else {
            print_file_information(argv[i]);
        }
    }
    return 0;
}
