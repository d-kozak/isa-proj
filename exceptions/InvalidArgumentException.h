#ifndef ISA_PROJ_INVALIDARGUMENTEXCEPTION_H
#define ISA_PROJ_INVALIDARGUMENTEXCEPTION_H


#include "BaseException.h"

/**
 * Exception raised when invalid arguments are passed into a method or functions
 */
class InvalidArgumentException : public BaseException{
public:
    InvalidArgumentException(string msg);
};


#endif //ISA_PROJ_INVALIDARGUMENTEXCEPTION_H
