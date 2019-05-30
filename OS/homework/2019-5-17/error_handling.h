#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
//--------------------------------------------
// FUNCTION: xstat
// stats about a file with error handling
// PARAMETERS:
// pathname -> path to file; statbuf -> structure to write the data to
//----------------------------------------------
bool xstat(const char* pathname, struct stat* statbuf);
//--------------------------------------------
// FUNCTION: xreaddir
// reads the contents of a directory with error checking
// // PARAMETERS:
// DIR* dir -> dir structure to read from
//----------------------------------------------
struct dirent* xreaddir(DIR* dir);
//--------------------------------------------
// FUNCTION: xopendir
// open directory with error handling
// PARAMETERS:
// path -> directory path
//----------------------------------------------
DIR* xopendir(const char* path);
//--------------------------------------------
// FUNCTION: xclosedir
// close directory with error handling
// PARAMETERS:
// dir -> directory to close
//----------------------------------------------
void xclosedir(DIR* dir);
