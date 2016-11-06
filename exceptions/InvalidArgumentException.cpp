//
// Created by david on 7.10.16.
//

#include "InvalidArgumentException.h"

InvalidArgumentException::InvalidArgumentException(string msg){
    this->_msg = msg;
    this->_name = "InvalidArgumentException";
}
