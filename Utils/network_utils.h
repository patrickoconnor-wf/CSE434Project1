#ifndef __NETWORK_UTILS_INCLUDED__
#define __NETWORK_UTILS_INCLUDED__
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>     /* for atoi() and exit() */
#include <unistd.h>     /* for gethostname */

char* get_host_ip();
#endif
