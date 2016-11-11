//
// Created by david on 6.10.16.
//

#include "Release.h"
#include "Ack.h"

void Release::performTask(AddressHandler & handler){
    IpAddress addressToRelease = _msg.getCiaddr();
    MacAddress address = _msg.getChaddr();
    handler.releaseAddress(address);

    Ack ack;
    ack.performTask(_msg,addressToRelease,handler);
}

string Release::toString(){
    return this->_name;
}

string Release::getLoggableName(){
    return this->_name;
}
