#include "Packet.h"
#include <iostream>

Packet::Packet(const char *action, const char *message) {
  this->action = allocate(action);
  this->message = allocate(message);
  this->hostName = new char[255];
  gethostname(this->hostName, 255);
  this->ipAddress = get_host_ip();
  this->sequence = 0;
}

Packet::~Packet() {
  delete [] this->action;
  delete [] this->message;
  delete [] this->hostName;
  delete [] this->ipAddress;
}

int Packet::getHeaderLen(const char *action_type) {
  Packet *empty = new Packet(action_type, "");
  return strlen(empty->serialize());
}

char* Packet::allocate(const char *copyFrom) {
  int bufferLen = strlen(copyFrom) + 1;
  char *buffer = new char[bufferLen];
  strncpy(buffer, copyFrom, bufferLen);
  buffer[bufferLen-1] = '\0';
  return buffer;
}

char* Packet::getAction() {
  return this->action;
}

char* Packet::getMessage() {
  return this->message;
}

char* Packet::getHostName() {
  return this->hostName;
}

char* Packet::getIpAddress() {
  return this->ipAddress;
}

char* Packet::serialize() {
  //Add to the total message size for the terminator and separators
  // TODO: Possible build this buffer in a function?
  int bufferLen = strlen(this->action) +
                  strlen(this->message) +
                  strlen(this->hostName) +
                  strlen(this->ipAddress) +
                  4;
  char *buffer = new char[bufferLen];
  snprintf(buffer, bufferLen, "%s|%s|%s\n%s", this->action, this->hostName, this->ipAddress, this->message);
  buffer[bufferLen-1] = '\0';
  return buffer;
}

Packet* Packet::deserialize(char *recv) {
  // TODO: Implement Deserialize
  std::vector<std::string> packetVector = split(recv, '\n');
  std::vector<std::string> headerVector = split(packetVector[0].c_str(), '|');
  std::string messageString = "";

  for(std::vector<std::string>::iterator it = ++packetVector.begin(); it != packetVector.end(); ++it) {
    messageString += *it + "\n";
  }
  Packet *packet = new Packet(headerVector[0].c_str(), messageString.c_str());

  return packet;
}

std::vector<std::string> split(const char *s, char delimiter) {

  std::stringstream ss(s);
  std::string entry;
  std::vector<std::string> vector;

  while (std::getline(ss, entry, delimiter)) {
    vector.push_back(entry);
  }
  return vector;

}
