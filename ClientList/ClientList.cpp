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
char* ClientList::FormatFilesList (char *message){
  std::vector<std::string> FileNames = split(message, ' ');
  this->fileNames = FileNames;
  static char ch[] = "ACK";
      return ch;
}
