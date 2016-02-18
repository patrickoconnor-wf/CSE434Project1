#ifndef __PACKET_DEFINED__
#define __PACKET_DEFINED__
#include <cstring>
#include <cstdio>
#include <string>
#include <sstream>
#include <unistd.h>
#include <vector>
#include "../Utils/network_utils.h"

class Packet {
  private:
    char *action;
    char *message;
    char *hostName;
    char *ipAddress;
    int sequence;
    char* allocate(const char *copyFrom);

  public:
    Packet(const char *action, const char *message);
    ~Packet();
    static int getHeaderLen(const char* action_type);
    char* getAction();
    char* getMessage();
    char* getHostName();
    char* getIpAddress();
    char* serialize();
    static Packet* deserialize(char *recv);
};

std::vector<std::string> split(const char *s, char delimiter);
#endif
