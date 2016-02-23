#include "ClientList.h"
#include <iostream>



ClientList::ClientList(char *hostName,char *ipAddress ) {
  this->hostName = hostName;
  this->ipAddress = ipAddress;
//  this->fileNames = new std::vector<std::string>;
}

ClientList::~ClientList() {
  delete [] this->hostName;
  delete [] this->ipAddress;
}
char* ClientList::formatFilesList (char *message){
  std::vector<std::string> FileNames = split(message, ' ');
  this->fileNames = FileNames;
  static char ch[] = "ACK";
      return ch;
}
char* ClientList::getHostName() {
  return this->hostName;
}

char* ClientList::getIpAddress() {
  return this->ipAddress;
}
bool ClientList::fileFoundInClient(const char *FileBeingSearched){
  bool Found = false ;
  std::string sthisFileName = std::string(FileBeingSearched);
    /* data */
  if(std::find(this->fileNames.begin(), this->fileNames.end(), sthisFileName) != this->fileNames.end()) {
   Found = true ;
  }
  return Found;
}
