//
// Created by david on 6.10.16.
//

#include "Discover.h"
#include "../exceptions/OutOfAddressException.h"


using namespace addressing;

void Discover::performTask(AddressHandler & handler){
    try {
        vector<unsigned char> mac = _msg.getItemAsVector(_msg.chaddr,_msg.size_chaddr);
        MacAddress macAddr(mac);
        IpAddress newAddr = handler.getAddressFor(macAddr);


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