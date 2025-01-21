#include "server.hpp"

int main() {
  server meow;
  meow.runServer();
  std::cout << "Meow. Server are runned" << std::endl;
  char buffer[1024] = "meow";
  meow.sendFromBuffer<std::size(buffer)>(&buffer);
  meow.stopServer();
  return 0;
}