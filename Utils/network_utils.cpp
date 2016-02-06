#include "network_utils.h"

char* get_host_ip() {
  char *hostBuffer = new char[255];
  gethostname(hostBuffer, 255);
  hostent *record = gethostbyname(hostBuffer);
  if(record == NULL)
	{
		printf("%s is unavailable\n", hostBuffer);
		exit(1);
	}
  in_addr *address = (in_addr *)record->h_addr;
	char *ip_address = inet_ntoa(*address);
  return ip_address;
}
