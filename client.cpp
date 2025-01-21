#include "client.hpp"

#include <iostream>

int main(int argc, const char** argv) {
  try {
    char buff[1024];
    client c;
    c.client_connect();
    c.readToBuffer<1024>(&buff);
    std::cout << buff << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  return 0;
}