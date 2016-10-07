//
// Created by david on 7.10.16.
//

#include "BaseException.h"

string BaseException::what() {
    return _msg;
}

string BaseException::toString(){
    string ret;
    ret.append(this->_name);
    ret.append(" -> ");
    ret.append(this->_msg);
    return ret;
}

string BaseException::getLoggableName(){
    return this->_name;
}