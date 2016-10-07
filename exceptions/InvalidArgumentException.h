//
// Created by david on 7.10.16.
//

#ifndef ISA_PROJ_INVALIDARGUMENTEXCEPTION_H
#define ISA_PROJ_INVALIDARGUMENTEXCEPTION_H


#include "BaseException.h"

class InvalidArgumentException : public BaseException{
public:
    InvalidArgumentException(string msg);
};


#endif //ISA_PROJ_INVALIDARGUMENTEXCEPTION_H
