//
// Created by david on 8.10.16.
//

#ifndef ISA_PROJ_SOCKETEXCEPTION_H
#define ISA_PROJ_SOCKETEXCEPTION_H


#include "BaseException.h"

class SocketException : public BaseException{
public:
    SocketException(string msg);
};


#endif //ISA_PROJ_SOCKETEXCEPTION_H
