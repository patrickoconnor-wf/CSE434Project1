#ifndef __CLIENTINFO_INCLUDED__
#define __CLIENTINFO_INCLUDED__

#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <vector>
#include "../Utils/network_utils.h"
#include "../Ports/ports.h"
#include "../Packet/packet.h"
class ClientInfo {
  private:
    char *hostName;
    char *ipAddress;
    std::vector<std::string> fileNames;
    static std::vector<ClientInfo> clients;
  public:
    ClientInfo(char *hostName,char *ipAddress);
    ~ClientInfo();
    void formatFilesList(char *message);
    char* getIpAddress();
    char* getHostName();
    static std::vector<ClientInfo> getClients();
    bool fileFoundInClient(std::string File);
    static std::string getClientsByFileName(std::string fileName);
    static bool removeClient(char* HostName, char *IpAddress);
  };
#endif
