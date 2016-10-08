//
// Created by david on 6.10.16.
//

#include "Socket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <err.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024


Socket::Socket(IpAddress & addr):_addr(addr) {

}

string Socket::getMessage() {
    int fd;                           // an incoming socket descriptor
    struct sockaddr_in server;        // server's address structure
    int n, r;
    char buffer[BUFFER_SIZE];              // receiving buffer
    struct sockaddr_in client;        // client's address structure
    socklen_t length;

//    server.sin_addr.s_addr

    server.sin_family = AF_INET;                     // set IPv4 addressing
    server.sin_addr.s_addr = htonl(INADDR_ANY);      // the server listens to any interface
    server.sin_port = htons(PORT_NUM);                   // the server listens on this port
}

void Socket::sendBroadcastMesage(string msg) {}

void Socket::sendMessage(string msg, IpAddress destination) {}

Socket::~Socket() {}

string Socket::getLoggableName() {
    return this->_name;
}

string Socket::toString() {
    stringstream ss;
    ss << this->_name << " -> ";
    return ss.str();
}
