//
// Created by david on 6.10.16.
//

#include "Request.h"

void Request::performTask(AddressHandler & handler){
    IpAddress serverAddres = handler.getServerAddress();
    if(serverAddres == _msg.getServerIdentifier()){
        // nothing for now, address is already assigned
    } else {
        MacAddress address = _msg.getChaddr();
        handler.releaseAddress(address);
    }
}


string Request::toString(){
    return this->_name;
}

string Request::getLoggableName(){
    return this->_name;
}
