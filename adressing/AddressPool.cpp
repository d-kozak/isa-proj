//
// Created by david on 5.10.16.
//

#include "AddressPool.h"

namespace addressing {

    AddressPool::AddressPool(IpAddress& first, int prefix,set<IpAddress> & reserved){}

    AddressPair::AddressPair(IpAddress & address){}
    void AddressPair::setIsFree(bool isFree){}
    bool AddressPair::isFree(){}
    IpAddress AddressPair::getAddress(){}
}
