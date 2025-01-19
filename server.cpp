#include <iostream>
#include <string>

#ifdef __linux__
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif  // linux

#ifdef _WIN32
#include <winsock2.h>
#endif  // _WIN32

class server {
 private:
#ifdef _WIN32  // for win
  SOCKET __sockfd;
#endif  // _WIN32

#ifdef __linux__  // for linux
  int __sockfd;
#endif  // linux

  // просто поля
  sockaddr_in __address;

 public:
  server(std::string adress = std::string("127.0.0.1"), int port = 8080) {
    __sockfd = socket(AF_INET,      // IPv4
                      SOCK_STREAM,  // TCP
                      0             // default
    );
    __address.sin_family = AF_INET;
    __address.sin_addr.s_addr = inet_addr(adress.c_str());
    __address.sin_port = htons(port);
  };
  ~server() {
#ifdef _WIN32
    closesocket(__sockfd);
#endif  // _WIN32

#ifdef __linux__
    close(__sockfd);
#endif  // linux
  };
};

int main(void) { return 0; }