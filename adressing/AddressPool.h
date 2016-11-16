//
// Created by david on 5.10.16.
//

#ifndef ISA_PROJ_ADDRESSPOOL_H
#define ISA_PROJ_ADDRESSPOOL_H

#include <iostream>
#include <list>
#include <set>
#include <mutex>
#include <sstream>
#include <map>
#include "MacAddress.h"
#include "Reservation.h"
#include "../BaseObject.h"
#include "../exceptions/InvalidArgumentException.h"


using namespace std;

/**
 * This enum specifies the state of ip address in pool
 * FREE no one uses the address
 * TO_BE_BINDED between DHCPOFFER and DHCPREQUEST, can still be used by somebody else if neccessary
 * BINDED currently in use by someone
 * EXPIRED after its lease finished, but still preferable for the old client if he sends request, can be used by somebody else if necceassary
 * DISABLED cannot use this address at all
 */
;
namespace addressing {

    typedef enum {
        FREE, TO_BE_BINDED, BINDED, EXPIRED, DISABLED,DIRECT_MAPPING
    } addressState;

    class AddressInfo : public BaseObject {
        const string _name = "AddressInfo";
        addressState _state;
        IpAddress _address;
        MacAddress* _mac = NULL;
        Timestamp* _timestamp = NULL;

    public:
        AddressInfo(IpAddress &address) : _address(address), _state(FREE) {}
        AddressInfo(IpAddress &address, addressState state) : _address(address), _state(state) {}

        void setState(addressState newState) {
            if(_state == DISABLED) {
                std::stringstream ss;
                ss << "Cannot change state of disabled address: ";
                ss << this->toString();
                throw InvalidArgumentException(ss.str());
            }
            this->_state = newState;
        }

        addressState getState() { return _state; }

        IpAddress getAddress();

        MacAddress *getMac() ;
        void setMac(MacAddress * mac);
        Timestamp *getTimestamp() const;

        void bindTheAddress(MacAddress & mac);
        void markAsToBeBinded(MacAddress & mac);

        virtual string toString();

        virtual string getLoggableName();

        virtual ~AddressInfo();
    };

    class AddressPool : public BaseObject {
        const string _name = "AddressPool";
        list <IpAddress> _reserved;
        list <AddressInfo> _addresses;
        map<MacAddress,IpAddress> _directMapping;

    public:
        AddressPool(IpAddress &net_address, int prefix, list <IpAddress> &reserved,
                    map<MacAddress, IpAddress> &direct_mapping);

        IpAddress getAddress(MacAddress & mac);
        const AddressInfo & confirmBindigFor(IpAddress & addr,MacAddress & mac);

        void releaseAddress(IpAddress &addr);
        void releaseAddress(MacAddress &mac);
        void addressExpired(IpAddress &addr);


        list<AddressInfo>& getAddresses(){
            return _addresses;
        }

        void printCurrentState();

        virtual string toString();

        virtual string getLoggableName();
    };

}


#endif //ISA_PROJ_ADDRESSPOOL_H
