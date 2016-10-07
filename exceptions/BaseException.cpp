//
// Created by david on 7.10.16.
//

#include "BaseException.h"
#include <sstream>

string BaseException::what() {
    return _msg;
}

string BaseException::toString(){
    stringstream ss;
    ss << this->_name;
    ss << " -> ";
    ss<< this->_msg;
    return ss.str();
}

string BaseException::getLoggableName(){
    return this->_name;
}