#ifndef ISA_PROJ_PARSEEXCEPTION_H
#define ISA_PROJ_PARSEEXCEPTION_H

#include <iostream>
#include "BaseException.h"

using namespace std;

/**
 * exception raised when any parsing function or method is given invalid input
 */
class ParseException :public BaseException{
public:
    ParseException(string msg);
};


#endif //ISA_PROJ_PARSEEXCEPTION_H
