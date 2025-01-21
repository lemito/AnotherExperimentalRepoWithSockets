#ifndef _CLIENT_H
#define _CLIENT_H

#include <arpa/inet.h>
#include <unistd.h>

#include <cstring>
#include <stdexcept>
#include <string>

class client {
 public:
  client(const std::string &adress = std::string("127.0.0.1"),
         int port = 8080) {
    _clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_clientfd == -1) {
      throw std::runtime_error("Failed : " + std::string(strerror(errno)));
    }
    _addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, adress.c_str(), &_addr.sin_addr) <= 0) {
      close(_clientfd);
      throw std::runtime_error("Failed : " + std::string(strerror(errno)));
    }
    _addr.sin_port = htons(port);
  }
  client(client &&) = delete;
  client(const client &) = delete;
  client &operator=(client &&) = delete;
  client &operator=(const client &) = delete;
  void client_connect() {
    int status = connect(_clientfd, (struct sockaddr *)&_addr, sizeof(struct sockaddr));
    if (status == -1) {
      throw std::runtime_error("Failed : " + std::string(strerror(errno)));
    }
  }
  ~client() { close(_clientfd); };

  void readToBuffer(std::string &buf) const {}
  void sendFromBuffer(const std::string &buf) const {}
  void readToBuffer(char **buf) const {}
  void sendFromBuffer(const char *buf) const {}
  template <size_t buf_siz>
  void readToBuffer(char (*buf)[buf_siz]) const {
    int status;
    if (-1 == (status = read(_clientfd, *buf, buf_siz))) {
      throw std::runtime_error("Failed : " + std::string(strerror(errno)));
    }
  }
  template <size_t buf_siz>
  void sendFromBuffer(char const (*buf)[buf_siz]) const {
    int status;
    if (-1 == (status = send(_clientfd, *buf, buf_siz, 0))) {
      throw std::runtime_error("Failed : " + std::string(strerror(errno)));
    }
  }

 private:
  int _clientfd{-1};
  struct sockaddr_in _addr {};
};

#endif