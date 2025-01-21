#include "server.hpp"

int main() {
  try {
    server meow;
    meow.runServer();
    std::cout << "Meow. Server are runned" << std::endl;
    char buffer[1024] = "meow";
    meow.sendFromBuffer<std::size(buffer)>(&buffer);
    meow.stopServer();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  return 0;
}