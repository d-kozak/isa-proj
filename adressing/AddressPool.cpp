//
// see header file for comments.
//
#include "AddressPool.h"
#include "../exceptions/OutOfAddressException.h"
#include "../exceptions/InvalidArgumentException.h"
#include "IpAddress.h"
#include <sstream>
#include <cmath>
#include <ctgmath>
#include <list>
#include <algorithm>

namespace addressing {


    AddressPool::AddressPool(IpAddress &net_address, int prefix, list <IpAddress> &reserved,
                             map<MacAddress, IpAddress> &direct_mapping) : _reserved(reserved), _addresses(),
                                                                           _directMapping(direct_mapping) {
        if (prefix < 0 || prefix > 32)
            throw InvalidArgumentException("Prefix must be a positive number between 0 and 32");

        int maxAddrCount = pow(2, 32 - prefix) - 2;
        IpAddress lastAddr = net_address.next_addr(maxAddrCount + 1);

        net_address = net_address.next_addr(); //skip the net_address one <- that one is for the server itself

        for (IpAddress addr = net_address.next_addr(); addr != lastAddr; addr = addr.next_addr()) {
            for (auto &item: direct_mapping) {
                if (item.second == addr) {
                    // do not need to store direct mapping in the pool
                    continue;
                }
            }

            bool isReserved = find(this->_reserved.begin(), this->_reserved.end(), addr) != this->_reserved.end();
            if (!isReserved) {
                // only store addresses that are not reserved
                AddressInfo pair(addr);
                this->_addresses.push_back(pair);
            }
        }

        if (DEBUG) {
            unsigned long count = _addresses.size();
            std::cout << "Allocated " << count << " addresses." << std::endl << "Aproximate size of the pool: "
                      << count * sizeof(IpAddress) << " bytes + " << sizeof(AddressPool) << " bytes of address pool"
                      << std::endl;
        }
    }

    void AddressPool::clean() {
        for (auto &addr : this->_addresses) {
            addr.clean();
        }
    }

    IpAddress AddressPool::getAddress(MacAddress &mac) {
        // check direct mapping first
        auto direct = this->_directMapping.find(mac);
        if (direct != this->_directMapping.end()) {
            return direct->second;
        }

        for (auto &item : this->_addresses) {
            if (item.getState() == FREE) {
                item.markAsToBeBinded(mac);
                return item.getAddress();
            }
        }
        // if no addresss is free, lets check to be binded addresses
        for (auto &item : this->_addresses) {
            if (item.getState() == TO_BE_BINDED) {
                // already in the correct state, but we are stealing somebody's ip to be :/
                item.markAsToBeBinded(mac);
                return item.getAddress();
            }
        }

        // try to find expired address that can be reassigned
        for (auto &item : this->_addresses) {
            if (item.getState() == EXPIRED) {
                item.markAsToBeBinded(mac);
                return item.getAddress();
            }
        }

        // no address found what so ever
        throw OutOfAddressException("No address is available");
    }

    AddressInfo AddressPool::confirmBindigFor(addressing::IpAddress &addr, addressing::MacAddress &mac) {
        //check static mapping first
        auto direct = this->_directMapping.find(mac);
        if (direct != this->_directMapping.end()) {
            //if it is a direct mapping, simply create a new addressInfo object and return it
            AddressInfo info((*direct).second, DIRECT_MAPPING);
            info.createTimestamp();
            info.setIsSharedInstance(false);
            return info;
        }


        //check whether ip was specified
        if (addr != NULL_IP) {
            // try to find given addressInfo
            for (auto &item : this->_addresses) {
                if (item.getAddress() == addr) {
                    if (item.getState() == TO_BE_BINDED || item.getState() == BINDED || item.getState() == EXPIRED) {
                        item.bindTheAddress(mac);
                        return item;
                    } else {
                        throw InvalidArgumentException("1 Given address is in invalid state ");
                    }
                }
            }
        }

        // if no ip was specified or given IP is not in the pool, try looking for the mac address
        for (auto &item : this->_addresses) {
            if (item.getMac() != NULL) {
                if (*item.getMac() == mac) {
                    if (item.getState() == TO_BE_BINDED || item.getState() == BINDED || item.getState() == EXPIRED) {
                        item.bindTheAddress(mac);
                        return item;
                    } else {
                        throw InvalidArgumentException("2 Given address is in invalid state");
                    }
                }
            }
        }

        // no address found what so ever
        throw InvalidArgumentException("Given address is not in the pool " + addr.toString());
    }

    void AddressPool::releaseAddress(IpAddress &addr) {
        for (auto &item : this->_addresses) {
            if (item.getAddress() == addr) {
                // for further reuse by the same host
                item.setState(TO_BE_BINDED);
                return;
            }
        }
        // if the address is not found, the operation is empty
    }

    void AddressPool::releaseAddress(MacAddress &mac) {
        for (auto &item : this->_addresses) {
            if (item.getMac() != NULL) {
                if (*item.getMac() == mac) {
                    // for further reuse by the same host
                    item.setState(TO_BE_BINDED);
                    return;
                }
            }
        }
        // if the address is not found, the operation is empty
    }

    void AddressPool::addressExpired(IpAddress &addr) {
        for (auto &item : this->_addresses) {
            if (item.getAddress() == addr) {
                // for further reuse by the same host
                item.setState(EXPIRED);
                return;
            }
        }
        throw InvalidArgumentException("This address " + addr.toString() + "is not in the pool");
    }

    void AddressPool::printCurrentState() {
        cout << this->toString();
    }

    string AddressPool::toString() const {
        stringstream ss;
        ss << this->_name << " -> " << "(" << endl << "\t{" << std::endl;
        for (auto &x : this->_addresses) {
            ss << "\t\t" << x.toString() << "," << std::endl;
        }
        ss << "\t}" << endl;
        ss << ", Reserved -> " << endl << "\t{" << std::endl;
        for (auto &x : this->_reserved) {
            ss << "\t\t" << x.toString() << "," << std::endl;
        }
        ss << "\t}";
        ss << "Static mapping -> {" << endl;
        for (auto &elem : this->_directMapping) {
            ss << "\t" << constRefToString(elem.first) << " => " << elem.second.asString() << endl;
        }
        ss << endl << ")" << endl;
        return ss.str();
    }

    string AddressPool::getLoggableName() const { return this->_name; }


    ////////////////////////////////////////////////////////////////////////////////////////////


    void AddressInfo::bindTheAddress(MacAddress &mac) {
        if (this->_mac == NULL)
            throw InvalidArgumentException("Mac is null in bindTheAdress");
        if (*this->_mac != mac) {
            throw InvalidArgumentException(
                    "Mac address set in the discover is diffrent the the on in the request, wierd internal error");
        }

        this->setState(BINDED);
        Timestamp *timestamp = new Timestamp;
        if (this->_timestamp != NULL)
            delete this->_timestamp;
        this->_timestamp = timestamp;
    }

    void AddressInfo::markAsToBeBinded(MacAddress &mac) {
        this->_state = TO_BE_BINDED;
        if (this->_mac != NULL)
            delete this->_mac;
        this->_mac = new MacAddress(mac.getPart(0), mac.getPart(1), mac.getPart(2), mac.getPart(3), mac.getPart(4),
                                    mac.getPart(5));
    }

    string AddressInfo::toString() const {
        stringstream ss;
        ss << this->_name << " -> (" << this->_address.toString() << ", ";
        switch (_state) {
            case FREE:
                ss << "FREE";
                break;
            case TO_BE_BINDED:
                ss << "TO_BE_BINDED";
                break;
            case BINDED:
                ss << "BINDED";
                break;
            case EXPIRED:
                ss << "EXPIRED";
                break;
            case RESERVED:
                ss << "RESERVED";
                break;
            case DIRECT_MAPPING:
                ss << "DIRECT_MAPPING";
                break;
        }

        ss << ")";
        return ss.str();
    }

    IpAddress AddressInfo::getAddress() {
        return this->_address;
    }

    string AddressInfo::getLoggableName() const { return this->_name; }

    void AddressInfo::clean() {
        if (_timestamp != NULL) {
            delete _timestamp;
            this->_timestamp = NULL;
        }
        if (_mac != NULL) {
            delete _mac;
            this->_mac = NULL;
        }
    }

    AddressInfo::~AddressInfo() {
    }

    MacAddress *AddressInfo::getMac() {
        return _mac;
    }

    Timestamp *AddressInfo::getTimestamp() const {
        return _timestamp;
    }
}
