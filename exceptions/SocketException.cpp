//
// Created by david on 8.10.16.
//

#include "SocketException.h"

SocketException::SocketException(string msg){
    this->_msg = msg;
    this->_name = "SocketException";
}
