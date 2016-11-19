//
// see header for comments
//

#include "InvalidArgumentException.h"

InvalidArgumentException::InvalidArgumentException(string msg){
    this->_msg = msg;
    this->_name = "InvalidArgumentException";
}
