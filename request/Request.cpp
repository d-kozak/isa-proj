//
// Created by david on 6.10.16.
//

#include "Request.h"

void Request::performTask(AddressHandler & handler){
    IpAddress serverAddress = handler.getServerAddress();
    if(serverAddress == _msg.getServerIdentifier()){
        MacAddress & mac = _msg.getChaddr();
        IpAddress & ciaddr = _msg.getCiaddr();
        handler.confirmBindingFor(ciaddr,mac);
    }
}


string Request::toString(){
    return this->_name;
}

string Request::getLoggableName(){
    return this->_name;
}
