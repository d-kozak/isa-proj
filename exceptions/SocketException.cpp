//
// see header for comments
//

#include "SocketException.h"

SocketException::SocketException(string msg){
    this->_msg = msg;
    this->_name = "SocketException";
}
