#include "file_utils.h"

const char* getFileSystemContents() {
  // Get the Current Working Directory
  char *cwdBuffer = new char[512];

  sprintf(cwdBuffer, "%s/%s", getcwd(cwdBuffer, 1024), "UDPClient/share/");
  DIR *open = opendir(cwdBuffer);
  struct stat filestat;
  if (open == NULL) {
    printf("%s%s\n", "ERROR: Directory structure is incorrect. The client should ",
    "be run using the makefile with a share folder inside the UDPClient folder");
    exit(1);
  }

  char *listings_str = new char[5120];
  struct dirent *dirp;
  while ((dirp = readdir(open)) != NULL) {
      std::string filename = cwdBuffer;
      filename += dirp->d_name;
      int f_size = getFileSize(filename.c_str());
      sprintf(listings_str, "%s|%d\n", dirp->d_name, f_size);
   }
   printf("%s\n", listings_str);
   return listings_str;

}

int getFileSize(const char *fileName) {
  std::ifstream file(fileName, std::ifstream::in | std::ifstream::binary);

  if (!file.good()) {
    printf("%s\n", "File is not open. The given file size will be incorrect.");
  }

  file.seekg(0, std::ios::end);
  int fileSize = file.tellg();
  file.close();
  return fileSize;
}
