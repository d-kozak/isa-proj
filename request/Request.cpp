//
// Created by david on 6.10.16.
//

#include "Request.h"

void Request::performTask(ResponseThread & thread){
    AddressHandler handler = thread.get_addressHandler();
    vector<unsigned char> vec = _msg.getItemAsVector(_msg.ciaddr, _msg.size_iaddr);
    IpAddress addr(vec);
}


string Request::toString(){
    return this->_name;
}

string Request::getLoggableName(){
    return this->_name;
}
