#include <cstdio>
#include <string>
#include <sstream>
#include <unistd.h>
#include <vector>
#include "../Utils/network_utils.h"
#include "../Ports/ports.h"
#include "../Packet/packet.h"
class ClientList {
  private:
    char *hostName;
    char *ipAddress;
    std::vector<std::string> fileNames;
  public:
    ClientList(char *hostName,char *ipAddress);
    ~ClientList();
    char* formatFilesList(char *message);
    char* getIpAddress();
    char* getHostName();
    bool fileFoundInClient(const char *File);


  };
