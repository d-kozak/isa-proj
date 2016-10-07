//
// Created by david on 5.10.16.
//

#include "AddressPool.h"
#include "../exceptions/OutOfAddressException.h"
#include <sstream>
#include <cmath>
#include <ctgmath>
#include <list>
#include <algorithm>

namespace addressing {


    AddressPool::AddressPool(IpAddress &first, int prefix, list <IpAddress> &reserved) : _reserved(reserved),_addresses() {
        int maxAddrCount = pow(2, 32 - prefix) - 2;
        IpAddress lastAddr = first.next_addr(maxAddrCount);

        for (IpAddress addr = first.next_addr(); addr != lastAddr; addr = addr.next_addr()) {
            if(find(this->_reserved.begin(),this->_reserved.end(),addr) != this->_reserved.end())
                continue;
            AddressPair pair(addr);
            this->_addresses.push_back(pair);
        }
    }

    IpAddress AddressPool::getAddress() {
        for (auto &item : this->_addresses) {
            if (item.isFree()) {
                item.setIsFree(false);
                return item.getAddress();
            }
        }
        throw OutOfAddressException("No address is available");
    }

    string AddressPool::toString() {
        stringstream ss;
        ss << this->_name << " -> " << "{" << std::endl;
        for (auto &x : this->_addresses) {
            ss << "\t" << x.toString() << "," << std::endl;
        }

        ss << "Reserved: " << std::endl;
        for (auto &x : this->_reserved) {
            ss << "\t" << x.toString() << "," << std::endl;
        }
        ss << "}";
        return ss.str();
    }

    string AddressPool::getLoggableName() { return this->_name; }


    ////////////////////////////////////////////////////////////////////////////////////////////


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

    IpAddress AddressPair::getAddress() {
        return this->_address;
    }

    string AddressPair::getLoggableName() { return this->_name; }
}
