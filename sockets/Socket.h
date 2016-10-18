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

class Socket : public BaseObject{
    const std::string _name = "Socket";
    const int DHCP_PORT_NUM = 1111; // correct is 68 :)
    IpAddress _addr;
    int _fd;

    void initSocket();
    void closeSocket();
    struct sockaddr_in initsockaddr(uint32_t addr,bool bindImmediately);
    struct sockaddr_in initsockaddr(string addr, bool bindImmediately);
public:
    Socket(IpAddress & addr);
    vector<unsigned char> getMessage();
    void setBroadCastFlag();
    void sendMessage(vector<unsigned char> msg, IpAddress destination);
    ~Socket();

    virtual string getLoggableName();
    virtual string toString();
};


#endif //ISA_PROJ_SOCKET_H
