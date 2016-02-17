#ifndef __FILE_UTILS_INCLUDED__
#define __FILE_UTILS_INCLUDED__
#include <dirent.h>     /* DIR* and struct dirent */
#include <fstream>      /* stream positions and file reading */
#include <iostream>     /* cout and printing */
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const char* getFileSystemContents();
int getFileSize(const char *fileName);
#endif
