//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_SOCKET_H
#define ISA_PROJ_SOCKET_H


#include "../BaseObject.h"

using namespace std;

class Socket : public BaseObject{
    const int _fd;

public:
    Socket(int fd);
    string getMessage();
    void sendMessage(string msg);
    ~Socket();
};


#endif //ISA_PROJ_SOCKET_H
