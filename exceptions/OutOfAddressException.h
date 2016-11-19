#ifndef ISA_PROJ_OUTOFADDRESSEXCEPTION_H
#define ISA_PROJ_OUTOFADDRESSEXCEPTION_H

#include <iostream>
#include "BaseException.h"

using namespace std;

/**
 * Exception raised when there are no available addresses in the address pool
 * @see Discover
 * @see AddressPool
 */
class OutOfAddressException : public BaseException{
public:
    OutOfAddressException(string msg);
};


#endif //ISA_PROJ_OUTOFADDRESSEXCEPTION_H
