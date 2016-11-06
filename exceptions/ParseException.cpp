//
// Created by david on 7.10.16.
//

#include "ParseException.h"

ParseException::ParseException(string msg){
    this->_msg = msg;
    this->_name = "ParseException";
}
