#include "ports.h"
#include <ctime>

int get_valid_port() {
  std::srand(std::time(0));
  return std::rand() % RANGE_PORT + MIN_PORT;
}
