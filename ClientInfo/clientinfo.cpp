#include "clientinfo.h"

// This makes sure the cpp and header refer to the same vector
std::vector<ClientInfo> ClientInfo::clients;

ClientInfo::ClientInfo(char *hostName, char *ipAddress ) {
  this->hostName = hostName;
  this->ipAddress = ipAddress;
//  this->fileNames = new std::vector<std::string>;
}

ClientInfo::~ClientInfo() {}

void ClientInfo::formatFilesList (const char *message){

  std::vector<std::string> files = split(message, '\n');
  // Erase what was in the fileNames vector
  std::fill(this->fileNames.begin(), this->fileNames.end(), "");
  // Extract file names without '|' delimeter
  for (auto fileName = files.begin(); fileName != files.end(); fileName++) {
    std::vector<std::string> temp = split(fileName->c_str(), '|');
    this->fileNames.push_back(temp[0]);
  }
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

void ClientInfo::addClient(ClientInfo *info) {
  clients.push_back(*info);
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
  std::string message = fileName + "|";

  for(auto iter = clients.begin(); iter != clients.end(); iter++) {
    // This flag is used to add the ipaddress if the filename being added is the
    // first file for the client being searched.
    bool firstFileAdded = true;
    bool wasUpdated = false;
      for(auto clientFile = iter->fileNames.begin(); clientFile != iter->fileNames.end(); clientFile++) {
        if (fileName.compare(*clientFile) == 0) {
          message += iter->getIpAddress();
          message += " ";
        }
      }
  }
  if (message.back() == ' ') {
    message.pop_back();
  }
  message += "\n";
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
