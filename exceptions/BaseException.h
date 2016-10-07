//
// Created by david on 7.10.16.
//

#ifndef ISA_PROJ_BASEEXCEPTION_H
#define ISA_PROJ_BASEEXCEPTION_H


#include "../BaseObject.h"

using namespace std;

class BaseException : BaseObject {
    const string _name = "BaseException";
protected:
    string _msg;
public:
    BaseException():_msg("NULL"){}
    virtual string what();
    virtual string toString();
    virtual string getLoggableName();
};


#endif //ISA_PROJ_BASEEXCEPTION_H
