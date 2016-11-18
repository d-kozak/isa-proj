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
        Offer offer;
        offer.performTask(_msg,newAddr,handler);
    }catch (OutOfAddressException & e){
        std::cerr << e.toString() << std::endl;
    }

}

string Discover::toString() const {
    return this->_name;
}

string Discover::getLoggableName() const {
    return this->_name;
}