#include "clientinfo.h"

// This makes sure the cpp and header refer to the same vector
std::vector<ClientInfo> ClientInfo::clients;

ClientInfo::ClientInfo(char *hostName, char *ipAddress ) {
  this->hostName = hostName;
  this->ipAddress = ipAddress;
//  this->fileNames = new std::vector<std::string>;
}

ClientInfo::~ClientInfo() {}

void ClientInfo::formatFilesList (char *message){
  std::vector<std::string> FileNames = split(message, ' ');
  this->fileNames = FileNames;
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

bool ClientInfo::fileFoundInClient(std::string FileBeingSearched){
  bool Found = false;
    /* data */
  if(std::find(this->fileNames.begin(), this->fileNames.end(), FileBeingSearched) != this->fileNames.end()) {
   Found = true;
  }
  return Found;
}

std::string ClientInfo::getClientsByFileName(std::string fileName){
  std::string message = "";
  for(std::vector<ClientInfo>::iterator iter = ClientInfo::getClients().begin(); iter != ClientInfo::getClients().end(); iter++) {
      if(iter->fileFoundInClient(fileName))
      {
        std::cout << iter->getHostName();
        message = message + std::string(iter->getIpAddress()) + " ";
        //message += message + iter->getHostName();
      }
  }
      return message;
}
bool ClientInfo::removeClient(char* HostName, char *IpAddress)
{ int i = 0;
  bool deleted = false;
  for(std::vector<ClientInfo>::iterator iter = ClientInfo::getClients().begin(); iter != ClientInfo::getClients().end(); iter++) {
    if (strcmp(HostName, iter->getHostName()) == 0 && strcmp(IpAddress, iter->getIpAddress()) == 0) {
      std::cout << iter->getHostName();
      clients.erase (clients.begin()+i);
      deleted = true;
      break;
    }
    i++;
  }
return deleted;

  //Clients.erase(std::remove(Clients.begin(),Clients.end(),)Clients.end());
}
