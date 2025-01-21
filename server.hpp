#ifndef _SERVER_H
#define	_SERVER_H

#include <iostream>
#include <string>

#ifdef __linux__
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif  // __linux__

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")

#include <winsock2.h>
#endif  // _WIN32

class server {
#ifdef _WIN32  // for win
  SOCKET _sockfd;
  SOCKET _conn;
#endif  // _WIN32

#ifdef __linux__  // for linux
  int _sockfd;
  int _conn;
#endif  // __linux__

  // просто поля
  sockaddr_in _address{};
  size_t _address_size = sizeof(_address);

 public:
  explicit server(const std::string& adress = std::string("127.0.0.1"),
                  int port = 8080) {
    _sockfd = socket(AF_INET,      // IPv4
                     SOCK_STREAM,  // TCP
                     0             // default
    );
    if (_sockfd < 0) {
      std::cerr << "Error creating socket" << std::endl;
      throw;
    } else {
      std::cout << "Socket created" << std::endl;
    }

    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = inet_addr(adress.c_str());
    _address.sin_port = htons(port);

    if (-1 == bind(_sockfd, reinterpret_cast<sockaddr*>(&_address),
                   sizeof(_address))) {
      std::cerr << "Error binding socket and address" << std::endl;
      throw;
    }

    if (-1 == listen(_sockfd, SOMAXCONN)) {
      std::cerr << "Error listening socket with SOMAXCONN = " << SOMAXCONN
                << std::endl;
      throw;
    }
  };
  ~server() {
#ifdef _WIN32
    closesocket(_conn);
    closesocket(_sockfd);
#endif  // _WIN32

#ifdef __linux__
    close(_conn);
    close(_sockfd);
#endif  // __linux__
  }
  void runServer() {
    std::cout << "Server starting..." << std::endl;

    if ((_conn = accept(_sockfd, reinterpret_cast<sockaddr*>(&_address),
                        reinterpret_cast<socklen_t*>(&_address_size)) < 0)) {
      std::cerr << "Error accepting conection" << std::endl;
      throw;
    }
  }

  void readToBuffer(std::string& buf) const {}
  void sendFromBuffer(const std::string& buf) const {}
  void readToBuffer(char** buf) const {}
  void sendFromBuffer(const char* buf) const {}
  template <size_t buf_siz>
  void readToBuffer(char (*buf)[buf_siz]) const {
    if (-1 == (status = read(_conn, buf, buf_siz))) {
      throw;
    }
  }
  template <size_t buf_siz>
  void sendFromBuffer(char const (*buf)[buf_siz]) const {
    if (-1 == (status = send(_conn, buf, buf_siz, 0))) {
      throw;
    }
  }
};

#endif