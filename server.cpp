#include "server.hpp"

int main() {
  try {
    char buffer[1024] = "meow";
    server meow;
    meow.runServer();
    std::cout << "Meow. Server are runned " << buffer << std::endl;
    meow.sendFromBuffer<std::size(buffer)>(&buffer);
    // meow.stopServer();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  return 0;
}