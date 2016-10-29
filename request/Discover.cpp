//
// Created by david on 6.10.16.
//

#include "Discover.h"
#include "../exceptions/OutOfAddressException.h"
#include "../constants.h"
#include "Offer.h"


using namespace addressing;

void Discover::performTask(AddressHandler & handler){
    try {
        MacAddress macAddr = _msg.getChaddr();
        IpAddress newAddr = handler.getAddressFor(macAddr);

        AbstractReply * reply = new Offer();
        reply->performTask(_msg,newAddr,handler);
        delete (Offer *)reply;

    }catch (OutOfAddressException & e){
        std::cerr << e.toString() << std::endl;
    }

}

string Discover::toString(){
    return this->_name;
}

string Discover::getLoggableName(){
    return this->_name;
}