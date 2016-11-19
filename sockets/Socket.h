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
    const int DHCP_PORT_LISTEN = 67;
    /**
     * port to which the replies are sent
     */
    const int DHCP_PORT_SEND = 68;
    /*
     * Ip address
     */
    IpAddress _addr;

    /**
     * socket descriptor of current uderlying socket
     */
    int _fd;

    /**
     * prepares the socket, calls housekeeping functions
     */
    void initSocket();

    /**
     * inits the socket with specified address
     * @param forListening specifies whether the socket should be binded
     * @return
     */
    struct sockaddr_in initsockaddr(uint32_t addr,bool forListening);
    /**
     * inits the socket with specified address
     * @param bindImmediately specifies whether the socket should be binded
     * @return
     */
    struct sockaddr_in initsockaddr(string addr, bool bindImmediately);
public:
    /**
     * create a socket
     * @param addr ip address
     */
    Socket(const IpAddress & addr);

    /**
     * reads the message from the socket
     * @return message
     */
    vector<unsigned char> getMessage();

    /**
     * sets broadcast flag to true
     */
    void setBroadcastFlag();

    /**
     * sends message msg to ip destination
     * @param msg
     * @param destination
     */
    void sendMessage(vector<unsigned char> msg, IpAddress destination);

    /**
     * closes the socket
     */
    void closeSocket() volatile;

    /**
     * destructor, tries to close the socket if it was opened before
     */
    ~Socket();

    virtual string getLoggableName() const ;
    virtual string toString() const;
};


#endif //ISA_PROJ_SOCKET_H
