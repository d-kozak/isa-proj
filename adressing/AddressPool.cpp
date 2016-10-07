//
// Created by david on 5.10.16.
//

#include "AddressPool.h"
#include <sstream>

namespace addressing {

    AddressPool::AddressPool(IpAddress &first, int prefix, set<IpAddress> &reserved) {}

    IpAddress AddressPool::getAddress() {}

    string AddressPool::toString() {}

    string AddressPool::getLoggableName() { return this->_name; }


    AddressPair::AddressPair(IpAddress &address) : _address(address), _isFree(true) {}

    void AddressPair::setIsFree(bool isFree) {
        this->_isFree = isFree;
    }

    bool AddressPair::isFree() {
        return this->_isFree;
    }

    string AddressPair::toString() {
        stringstream ss;
        ss << this->_name << " -> (" << this->_address.toString() << ", " << (this->_isFree ? "free" : "reserved")
           << ")";
        return ss.str();
    }

    string AddressPair::getLoggableName() { return this->_name; }
}
