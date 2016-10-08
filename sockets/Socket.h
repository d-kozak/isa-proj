//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_SOCKET_H
#define ISA_PROJ_SOCKET_H


#include "../BaseObject.h"
#include "../adressing/IpAddress.h"
#include <sstream>

using namespace addressing;

class Socket : public BaseObject{
    const std::string _name = "Socket";
    const int PORT_NUM = 1111;
    IpAddress _addr;
public:
    Socket(IpAddress & addr);
    string getMessage();
    void sendBroadcastMesage(string msg);
    void sendMessage(string msg, IpAddress destination);
    ~Socket();

    virtual string getLoggableName();
    virtual string toString();
};


#endif //ISA_PROJ_SOCKET_H
