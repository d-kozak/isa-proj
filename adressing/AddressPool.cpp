//
// Created by david on 5.10.16.
//

#include "AddressPool.h"
#include "../exceptions/OutOfAddressException.h"
#include "../exceptions/InvalidArgumentException.h"
#include <sstream>
#include <cmath>
#include <ctgmath>
#include <list>
#include <algorithm>

namespace addressing {


    AddressPool::AddressPool(IpAddress &net_address, int prefix, list <IpAddress> &reserved) : _reserved(reserved),_addresses() {
        if(prefix < 0 || prefix > 32)
            throw InvalidArgumentException("Prefix must be a positive number between 0 and 32");

        int maxAddrCount = pow(2, 32 - prefix) - 2;
        IpAddress lastAddr = net_address.next_addr(maxAddrCount + 1);

        net_address = net_address.next_addr(); //skip the net_address one <- that one is for the server itself

        for (IpAddress addr = net_address.next_addr(); addr != lastAddr; addr = addr.next_addr()) {
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

    void AddressPool::releaseAddress(IpAddress &addr){
        for(auto & item : this->_addresses){
            if(item.getAddress() == addr){
                item.setIsFree(true);
                return;
            }
        }
        throw InvalidArgumentException("This address " + addr.toString() + "is not in the pool");
    }

    void AddressPool::printCurrentState() {
        cout << this->toString();
    }

    string AddressPool::toString() {
        stringstream ss;
        ss << this->_name << " -> " << "(" << endl <<  "\t{" << std::endl;
        for (auto &x : this->_addresses) {
            ss << "\t\t" << x.toString() << "," << std::endl;
        }
        ss << "\t}" << endl;
        ss << ", Reserved -> " << endl << "\t{" << std::endl;
        for (auto &x : this->_reserved) {
            ss << "\t\t" << x.toString() << "," << std::endl;
        }
        ss << "\t}" << endl << ")" << endl;
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
