#include "Packet.h"

Packet::Packet(const char *action, const char *message) {
  this->action = allocate(action);
  this->message = allocate(message);
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

char* Packet::serialize() {
  //Add 2 to the total message size for the terminator and separator
  char *hostBuffer = new char[255];
  gethostname(hostBuffer, 255);
  // TODO: Possible build this buffer in a function?
  // TODO: Implement function to retrieve IP and append it after hostname
  int bufferLen = strlen(this->action) + strlen(this->message) + strlen(hostBuffer) + 3;
  char *buffer = new char[bufferLen];
  snprintf(buffer, bufferLen, "%s|%s\n%s", this->action, hostBuffer, this->message);
  buffer[bufferLen-1] = '\0';
  return buffer;
}

Packet* Packet::deserialize() {
  // TODO: Implement Deserialize
  return new Packet("", "");
}
