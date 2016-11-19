//
// Created by david on 6.10.16.
//

#include "Release.h"
#include "Ack.h"

void Release::performTask(AddressHandler & handler){
    MacAddress address = _msg.getChaddr();
    handler.releaseAddress(address);
}

string Release::toString() const{
    return this->_name;
}

string Release::getLoggableName() const{
    return this->_name;
}
