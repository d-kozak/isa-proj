//
// see header for comments
//

#include "ParseException.h"

ParseException::ParseException(string msg){
    this->_msg = msg;
    this->_name = "ParseException";
}
