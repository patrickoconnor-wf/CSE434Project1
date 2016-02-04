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
