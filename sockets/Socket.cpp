//
// see header for details
//
#include "Socket.h"
#include "../exceptions/SocketException.h"
#include "../constants.h"

#include <arpa/inet.h>
#include <err.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/**
 * flag from main to determine if the socket error was raised on purpose
 */
extern volatile int isInterrupted;

Socket::Socket() : _listenSocketfd(-1), _answerSocketfd(-1) {
    initListeningSocket();
    initAnsweringSocket();
}

void Socket::initListeningSocket() {
    if (DEBUG)
        printf("opening UDP listening socket(...)\n");
    if ((_listenSocketfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {    // create the _listenAddr UDP socket
        perror("Socket");
        throw SocketException("socket() failed");
    }

    memset(&_listenAddr, 0, sizeof(_listenAddr));
    _listenAddr.sin_family = AF_INET;                     // set IPv4 addressing
    _listenAddr.sin_addr.s_addr = htonl(INADDR_ANY);           // the _listenAddr listens to any interface
    _listenAddr.sin_port = htons(DHCP_PORT_LISTEN);              // the _listenAddr listens on this port

    if (DEBUG)
        printf("binding to the port %d (%d)\n", DHCP_PORT_LISTEN, _listenAddr.sin_port);
    if (bind(this->_listenSocketfd, (struct sockaddr *) &_listenAddr, sizeof(_listenAddr)) == -1) { // binding with the port
        perror("Socket");
        throw SocketException("bind() failed");
    }
}

void Socket::initAnsweringSocket() {
    if (DEBUG)
        printf("opening UDP answering socket(...)\n");
    if ((_answerSocketfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {    // create the _answerAddr UDP socket
        perror("Socket");
        throw SocketException("socket() failed");
    }

    IpAddress broadcast = IpAddress::getBroadcastAddr();

    memset(&_answerAddr, 0, sizeof(_answerAddr));
    _answerAddr.sin_family = AF_INET;                     // set IPv4 addressing
    _answerAddr.sin_addr.s_addr = htonl(broadcast.getAddrForSocket());           // the _answerAddr will send broadcassts
    _answerAddr.sin_port = htons(DHCP_PORT_SEND);              // the _answerAddr sends messages to  this port

    int on = 1;                                   // set socket to send broadcast messages
    if ((setsockopt(_answerSocketfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on))) == -1) {
        perror("Socket");
        err(1, "setsockopt failed()");
    }
}

void Socket::closeSockets() volatile {
    if(_listenSocketfd != -1) {
        if (DEBUG)
            printf("closing listening socket\n");
        if (_listenSocketfd != -1) {
            if (close(_listenSocketfd) == -1) {
                perror("Socket");
                throw SocketException("close() failed");
            }
            _listenSocketfd = -1;
        }
    }

    if(_answerSocketfd != -1) {
        if (DEBUG)
            printf("closing answering socket\n");
        if (_answerSocketfd != -1) {
            if (close(_answerSocketfd) == -1) {
                perror("Socket");
                throw SocketException("close() failed");
            }
            _answerSocketfd = -1;
        }
    }
}

vector<unsigned char> Socket::getMessage() {
    ssize_t msg_size;
    vector<unsigned char> data;
    data.resize(BUFFER_SIZE);

    socklen_t length = sizeof(_listenAddr);
    msg_size = recvfrom(_listenSocketfd, data.data(), BUFFER_SIZE, 0, (struct sockaddr *) &_listenAddr, &length);
    if (msg_size == -1) {
        if (!isInterrupted)
            perror("Socket");
        throw SocketException("recvfrom() failed");
    }

    if (DEBUG)
        printf("Request received from %s, port %d\n", inet_ntoa(_listenAddr.sin_addr), ntohs(_listenAddr.sin_port));
    return data;
}

void Socket::broadcastMessage(vector<unsigned char> msg) volatile {
    ssize_t count;
    socklen_t len = sizeof(_answerAddr);
    count = sendto(_answerSocketfd, msg.data(), msg.size(), 0, (struct sockaddr *) &_answerAddr, len);  // send data to the server
    if (count == -1) {                      // check if data was sent correctly
        perror("Socket");
        throw SocketException("sendto() failed");
    } else if (count != msg.size()) {
        perror("Socket");
        throw SocketException("sendto(): buffer written partially");
    } else if (DEBUG)
        printf("Reply send...\n");
}

Socket::~Socket() {
    closeSockets();
}

string Socket::getLoggableName() const {
    return this->_name;
}

string Socket::toString() const {
    stringstream ss;
    ss << this->_name << " -> " << "{" << "}" << endl;
    return ss.str();
}
