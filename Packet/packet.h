#ifndef __PACKET_DEFINED__
#define __PACKET_DEFINED__
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include "../Utils/network_utils.h"

class Packet {
  private:
    char *action;
    char *message;
    char* allocate(const char *copyFrom);

  public:
    Packet(const char *action, const char *message);
    static int getHeaderLen(const char* action_type);
    char* getAction();
    char* getMessage();
    char* serialize();
    Packet* deserialize();
};
#endif
