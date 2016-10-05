//
// Created by david on 5.10.16.
//

#include "AddressHandler.h"




namespace addressing{
    AddressHandler::AddressHandler(IpAddress &first, int prefix, set<IpAddress> &reserved) {}


    IpAddress AddressHandler::getAddressFor(MacAddress & mac){}
    void AddressHandler::releaseAddress(MacAddress & mac){}


    AddressCollector::AddressCollector(AddressHandler & ha){}
    AddressCollector::void start(){}
    AddressCollector::void interrupt(){}
    AddressCollector::~AddressCollector(){}
}