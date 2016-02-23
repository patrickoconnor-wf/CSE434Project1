#include "clientinfo.h"

// This makes sure the cpp and header refer to the same vector
std::vector<ClientInfo> ClientInfo::clients;

ClientInfo::ClientInfo(char *hostName, char *ipAddress ) {
  this->hostName = hostName;
  this->ipAddress = ipAddress;
//  this->fileNames = new std::vector<std::string>;
}

ClientInfo::~ClientInfo() {}

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

std::vector<ClientInfo> ClientInfo::getClients() {
  return clients;
}

bool ClientInfo::fileFoundInClient(const char *FileBeingSearched){
  bool Found = false;
  std::string sthisFileName = std::string(FileBeingSearched);
    /* data */
  if(std::find(this->fileNames.begin(), this->fileNames.end(), sthisFileName) != this->fileNames.end()) {
   Found = true;
  }
  return Found;
}

std::string ClientInfo::getClientsByFileName(const char *fileName){
  std::string message = "";
  for(std::vector<ClientInfo>::iterator iter = clients.begin(); iter != clients.end(); iter++) {
      if(iter->fileFoundInClient(fileName))
      {
        std::cout << iter->getHostName();
        //message += message + iter->getHostName();
      }
  }
      return message.c_str();
}

void ClientInfo::removeClient(char* HostName, char *IpAddress)
{
  //Clients.erase(std::remove(Clients.begin(),Clients.end(),)Clients.end());
}
