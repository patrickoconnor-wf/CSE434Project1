#include "clientinfo.h"
#include <iostream>

ClientInfo::ClientInfo(char *hostName,char *ipAddress ) {
  this->hostName = hostName;
  this->ipAddress = ipAddress;
//  this->fileNames = new std::vector<std::string>;
}

ClientInfo::~ClientInfo() {
  delete [] this->hostName;
  delete [] this->ipAddress;
}
char* ClientInfo::formatFilesList (char *message){
  std::vector<std::string> FileNames = split(message, ' ');
  this->fileNames = FileNames;
  static char ch[] = "ACK";
      return ch;
}
char* ClientInfo::getHostName() {
  return this->hostName;
}

char* ClientInfo::getIpAddress() {
  return this->ipAddress;
}
bool ClientInfo::fileFoundInClient(const char *FileBeingSearched){
  bool Found = false ;
  std::string sthisFileName = std::string(FileBeingSearched);
    /* data */
  if(std::find(this->fileNames.begin(), this->fileNames.end(), sthisFileName) != this->fileNames.end()) {
   Found = true ;
  }
  return Found;
}
