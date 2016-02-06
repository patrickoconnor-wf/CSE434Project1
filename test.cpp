#include <stdio.h>      /* for printf() and fprintf() */
#include "Packet/packet.h"
#include <dirent.h>
#include <iostream>
#include "Utils/network_utils.h"

int main(int argc, char const *argv[]) {
  Packet *packet = new Packet::Packet("UPDATE", "MESSAGE");
  printf("%s\n", packet->getAction());
  printf("%s\n", packet->getMessage());
  printf("%s\n", packet->serialize());

  DIR *open = opendir("/Users/patrickoconnor/Documents/");
  struct dirent *dirp;
  while ((dirp = readdir(open)) != NULL) {
       std::cout << dirp->d_name << std::endl;

   }

   Packet::determinePacketCount();
  return 0;
}
