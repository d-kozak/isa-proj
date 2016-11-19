//
// see header for comments
//

#include "BaseException.h"
#include <sstream>

string BaseException::what() {
    return _msg;
}

string BaseException::toString() const {
    stringstream ss;
    ss << this->_name;
    ss << " -> ";
    ss<< this->_msg;
    return ss.str();
}

string BaseException::getLoggableName() const {
    return this->_name;
}