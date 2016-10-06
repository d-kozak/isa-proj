//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_MAINSOCKET_H
#define ISA_PROJ_MAINSOCKET_H


#include "../BaseObject.h"
#include "../adressing/IpAddress.h"
#include "Socket.h"

using namespace std;

class MainSocket : public BaseObject{
    static const int PORT_NUM = 666;
    const int _fd;

public:
    MainSocket(addressing::IpAddress & srvr_addr);
    Socket getConnection();
    ~MainSocket();
};


#endif //ISA_PROJ_MAINSOCKET_H
