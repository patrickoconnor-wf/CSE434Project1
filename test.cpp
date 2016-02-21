#include <stdio.h>      /* for printf() and fprintf() */
#include "Packet/packet.h"
#include <dirent.h>
#include <iostream>
#include "Utils/network_utils.h"

int main(int argc, char const *argv[]) {
  Packet *packet = new Packet::Packet("Delete", "MESSAGE new one for new message ");
  printf("%s\n", packet->getAction());
  printf("%s\n", packet->getMessage());
  printf("%s\n", packet->serialize());
  char *Words = packet->serialize();
  Packet *newPacket = packet->deserialize(Words);
  printf("%s\n", newPacket->getAction());
  printf("%s\n", newPacket->getMessage());
  //printf("%s\n", newPacket->serialize());
  //DIR *open = opendir("/Users/patrickoconnor/Documents/");
  //struct dirent *dirp;
  //while ((dirp = readdir(open)) != NULL) {
  //     std::cout << dirp->d_name << std::endl;

   //}

   //printf("%d\n", Packet::getHeaderLen("UPDATE"));
  return 0;
}
