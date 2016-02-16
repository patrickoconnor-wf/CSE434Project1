#include "file_utils.h"

const char* getFileSystemContents() {
  std::string share_dir = "./UDPClient/share";
  DIR *open = opendir(share_dir.c_str());
  struct stat filestat;
  if (open == NULL) {
    printf("%s%s\n", "ERROR: Directory structure is incorrect. The client should ",
    "be run using the makefile with a share folder inside the UDPClient folder");
    exit(1);
  }

  std::string listings_str = "";
  struct dirent *dirp;
  while ((dirp = readdir(open)) != NULL) {
       std::cout << dirp->d_name << std::endl;
       char *d_name = dirp->d_name;
       std::string filename = share_dir;
       filename += "/";
       filename += d_name;
      //  if (stat(filename.c_str(), &filestat)) continue;
      //  if (S_ISDIR(filestat.st_mode)) continue;
       long f_size = getFileSize(d_name);
       listings_str += d_name;
       listings_str += "|";
       listings_str += std::to_string(f_size);
       listings_str += "\n";
   }
   std::cout << listings_str << std::endl;
   const char *buffer = listings_str.c_str();
   return buffer;
}

long getFileSize(const char *fileName) {
    struct stat filestat;
    // std::streampos begin,end;
    // std::ifstream in(fileName, std::ios::binary);
    // begin = in.tellg();
    // in.seekg(0, in.end);
    // end = in.tellg();
    // std::cout << "Begin: " << begin << std::endl;
    // std::cout << "End: " << end << std::endl;
    // in.close();
    // return end;
    int rc = stat(fileName, &filestat);
    return rc == 0 ? filestat.st_size : -1;
}
