#ifndef _CLIENT_H
#define _CLIENT_H

#include <arpa/inet.h>
#include <unistd.h>

#include <string>

class client {
 public:
  client(const std::string &adress = std::string("127.0.0.1"),
         int port = 8080) {
    if ((socket(_clientfd, SOCK_STREAM, 0)) == -1) {
      throw;
    }
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = inet_addr(adress.c_str());
    _addr.sin_port = htons(port);
  }
  client(client &&) = delete;
  client(const client &) = delete;
  client &operator=(client &&) = delete;
  client &operator=(const client &) = delete;
  void client_connect() {
    int status;
    if ((status = connect(_clientfd, (struct sockaddr *)&_addr,
                          sizeof(_addr))) == -1) {
      throw;
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
    if (-1 == (status = read(_clientfd, buf, buf_siz))) {
      throw;
    }
  }
  template <size_t buf_siz>
  void sendFromBuffer(char const (*buf)[buf_siz]) const {
    int status;
    if (-1 == (status = send(_clientfd, buf, buf_siz, 0))) {
      throw;
    }
  }

 private:
  int _clientfd;
  struct sockaddr_in _addr;
};

#endif