//
// Created by david on 7.10.16.
//

#ifndef ISA_PROJ_PARSEEXCEPTION_H
#define ISA_PROJ_PARSEEXCEPTION_H

#include <iostream>
#include "BaseException.h"

using namespace std;

class ParseException :public BaseException{
public:
    ParseException(string msg);
};


#endif //ISA_PROJ_PARSEEXCEPTION_H
