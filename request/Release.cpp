//
// Created by david on 6.10.16.
//

#include "Release.h"

void Release::performTask(AddressHandler & handler){
    IpAddress addressToRelease = _msg.getCiaddr();
    MacAddress address = _msg.getChaddr();
    handler.releaseAddress(address);


}

string Release::toString(){
    return this->_name;
}

string Release::getLoggableName(){
    return this->_name;
}
