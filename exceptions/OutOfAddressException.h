//
// Created by david on 7.10.16.
//

#ifndef ISA_PROJ_OUTOFADDRESSEXCEPTION_H
#define ISA_PROJ_OUTOFADDRESSEXCEPTION_H

#include <iostream>
#include "BaseException.h"

using namespace std;

class OutOfAddressException : public BaseException{
public:
    OutOfAddressException(string msg);
};


#endif //ISA_PROJ_OUTOFADDRESSEXCEPTION_H
