#ifndef __PACKET_DEFINED__
#define __PACKET_DEFINED__
#include <cstring>
#include <cstdio>

class Packet {
  private:
    char *action;
    char *message;
    char* allocate(const char *copyFrom);

  public:
    Packet(const char *action, const char *message);
    char* getAction();
    char* getMessage();
    char* serialize();
    Packet* deserialize();
};
#endif
