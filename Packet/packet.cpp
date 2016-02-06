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
  //Add to the total message size for the terminator and separators
  char *hostBuffer = new char[255];
  gethostname(hostBuffer, 255);
  char *hostIp = get_host_ip();
  // TODO: Possible build this buffer in a function?
  int bufferLen = strlen(this->action) +
                  strlen(this->message) +
                  strlen(hostBuffer) +
                  strlen(hostIp) +
                  4;
  char *buffer = new char[bufferLen];
  snprintf(buffer, bufferLen, "%s|%s|%s\n%s", this->action, hostBuffer, hostIp, this->message);
  buffer[bufferLen-1] = '\0';
  return buffer;
}

Packet* Packet::deserialize() {
  // TODO: Implement Deserialize
  return new Packet("", "");
}
