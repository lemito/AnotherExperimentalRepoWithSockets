#include "client.hpp"

#include <iostream>

int main(int argc, const char** argv) {
  char buff[1024];
  client c;
  c.client_connect();
  c.readToBuffer<1024>(&buff);
  std::cout << buff << std::endl;
  return 0;
}