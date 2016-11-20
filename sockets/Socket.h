//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_SOCKET_H
#define ISA_PROJ_SOCKET_H


#include "../BaseObject.h"
#include "../adressing/IpAddress.h"
#include <sstream>
#include <vector>

using namespace addressing;

/**
 * Class wraps communication via BSD socket into methods
 */
class Socket : public BaseObject{
    const std::string _name = "Socket";
    /**
     * port where dhcp should listen
     */
    const uint16_t DHCP_PORT_LISTEN = 67;
    /**
     * port to which the replies are sent
     */
    const uint16_t  DHCP_PORT_SEND = 68;

    /**
     * socket descriptor of socket listening at port 67
     */
    int _listenSocketfd;

    /**
     * listen address
     */
    sockaddr_in _listenAddr;


    /**
     * socket descriptor of socket sending broadcast to port 68
     */
    int _answerSocketfd;

    /**
     * answer address
     */
    sockaddr_in _answerAddr;


    /**
     * prepares the listening socket, calls housekeeping functions
     */
    void initListeningSocket();

    /**
     * prepares the answering socket, calls housekeeping functions
     */
    void initAnsweringSocket();
public:
    /**
     * creates two sockets and calls all housekeeping functions on them
     * @throws SocketException if the socket functions return wrong ret val
     */
    Socket();

    /**
     * reads the message from the socket
     * @return message
     */
    vector<unsigned char> getMessage();


    /**
     * broadcasts the message
     * @param msg
     */
    void broadcastMessage(vector<unsigned char> msg) volatile ;

    /**
     * closes the socket
     */
    void closeSockets() volatile;

    /**
     * destructor, closes the socket if they were opened
     */
    ~Socket();

    virtual string getLoggableName() const ;
    virtual string toString() const;
};


#endif //ISA_PROJ_SOCKET_H
