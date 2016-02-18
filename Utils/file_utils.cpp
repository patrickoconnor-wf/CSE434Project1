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

  std::string listings_str = "";
  struct dirent *dirp;
  while ((dirp = readdir(open)) != NULL) {
    std::string filename = cwdBuffer;
    filename += dirp->d_name;
    if (stat(filename.c_str(), &filestat)) continue; // Populates filestat
    if (S_ISDIR(filestat.st_mode)) continue; // Breaks loop if not file
    int f_size = getFileSize(filename.c_str());

    // This is a very ugly implementation but it means I don't have to
    // allocate another C String just to use sprintf for formatting
    listings_str += dirp->d_name;
    listings_str += "|";
    listings_str += std::to_string(f_size);
    listings_str += "\n";
   }
   return listings_str.c_str();

}

int getFileSize(const char *fileName) {
  std::ifstream file(fileName, std::ifstream::in | std::ifstream::binary);

  if (!file.good()) {
    printf("%s\n", "File is not in good state. The given file size will be incorrect.");
  }

  file.seekg(0, std::ios::end);
  int fileSize = file.tellg();
  file.close();
  return fileSize;
}
