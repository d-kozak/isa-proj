#ifndef ISA_PROJ_SOCKETEXCEPTION_H
#define ISA_PROJ_SOCKETEXCEPTION_H


#include "BaseException.h"

/**
 * Exception raised when any of the underlying socket function returns error ret val
 * @see Socket
 */
class SocketException : public BaseException{
public:
    SocketException(string msg);
};


#endif //ISA_PROJ_SOCKETEXCEPTION_H
