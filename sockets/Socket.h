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
    const int DHCP_PORT_LISTEN = 67; // correct is 67 :)
    const int DHCP_PORT_SEND = 68; // correct is 68 :)
    IpAddress _addr;
    int _fd;

    void initSocket();
    void closeSocket();
    struct sockaddr_in initsockaddr(uint32_t addr,bool forListening);
    struct sockaddr_in initsockaddr(string addr, bool bindImmediately);
public:
    Socket(const IpAddress & addr);
    vector<unsigned char> getMessage();
    void setBroadcastFlag();
    void sendMessage(vector<unsigned char> msg, IpAddress destination);
    ~Socket();

    virtual string getLoggableName() const ;
    virtual string toString() const;
};


#endif //ISA_PROJ_SOCKET_H
