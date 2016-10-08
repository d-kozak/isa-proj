//
// Created by david on 6.10.16.
//

#include "Socket.h"
#include "../exceptions/SocketException.h"

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
#include <vector>

#define BUFFER_SIZE 1024


Socket::Socket(IpAddress &addr) : _addr(addr), _fd(-1) {}

string Socket::getMessage() {
    ssize_t msg_size;
    vector<char> data;
    data.resize(BUFFER_SIZE);
    struct sockaddr_in client;        // client's address structure
    socklen_t length;

    this->initSocket();
    this->initsockaddr(this->_addr.getAddrForSocket(), true);

    length = sizeof(client);

    while ((msg_size = recvfrom(_fd, data.data(), BUFFER_SIZE, 0, (struct sockaddr *) &client, &length)) >= 0) {
        printf("Request received from %s, port %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        cout << data.data() << endl;
    }
    if (msg_size == -1)
        throw SocketException("recvfrom() failed");
    string s(data.begin(), data.end());
    this->closeSocket();
    return s;
}

struct sockaddr_in Socket::initsockaddr(string addr, bool bindImmediately) {
    return this->initsockaddr(inet_addr(addr.c_str()), bindImmediately);
}

struct sockaddr_in Socket::initsockaddr(uint32_t addr, bool bindImmediately) {
    struct sockaddr_in server;                      // server's address structure
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;                     // set IPv4 addressing
    server.sin_addr.s_addr = htonl(addr);           // the server listens to any interface
    server.sin_port = htons(DHCP_PORT_NUM);              // the server listens on this port

    if (bindImmediately) {
        printf("binding to the port %d (%d)\n", DHCP_PORT_NUM, server.sin_port);
        if (bind(this->_fd, (struct sockaddr *) &server, sizeof(server)) == -1) // binding with the port
            throw SocketException("bind() failed");
    }
    return server;
}

void Socket::initSocket() {
    printf("opening UDP socket(...)\n");
    if ((_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)     // create the server UDP socket
        throw SocketException("socket() failed");
}

void Socket::closeSocket() {
    printf("closing socket\n");
    if (close(_fd) == -1) {
        throw SocketException("close() failed");
    }
    _fd = -1;
}

void Socket::setBroadCastFlag() {
    int on = 1;                                   // set socket to send broadcast messages
    if ((setsockopt(_fd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on))) == -1)
        err(1, "setsockopt failed()");
}

void Socket::sendMessage(string msg, IpAddress destination) {
    ssize_t count;
    this->initSocket();
    sockaddr_in server = this->initsockaddr(destination.asString(), false);
    socklen_t len = sizeof(server);

    if (destination.isBroadcastAddr())
        this->setBroadCastFlag();
    count = sendto(_fd, msg.c_str(), msg.size(), 0, (struct sockaddr *) &server, len);  // send data to the server
    if (count == -1)                                 // check if data was sent correctly
        throw SocketException("sendto() failed");
    else if (count != msg.size())
        throw SocketException("sendto(): buffer written partially");

    this->closeSocket();
}

Socket::~Socket() {
    if (_fd != -1) {
        try{
            this->closeSocket();
        } catch (SocketException & e) {
            cerr << e.what();
        }
    }
}

string Socket::getLoggableName() {
    return this->_name;
}

string Socket::toString() {
    stringstream ss;
    ss << this->_name << " -> " << "{" << endl;
    ss << "\t" << this->_addr.toString() << endl;
    ss << "}";
    return ss.str();
}
