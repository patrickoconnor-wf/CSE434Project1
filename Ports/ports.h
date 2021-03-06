#ifndef __PORTS_INCLUDED__
#define __PORTS_INCLUDED__
#include <cstdlib>
const int MAX_PORT = 4922; //Technically, 4923 is valid but that is reserved for the server
const int MIN_PORT = 4824;
const int RANGE_PORT = MAX_PORT - MIN_PORT;

int get_valid_port();
#endif
