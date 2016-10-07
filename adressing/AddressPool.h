//
// Created by david on 5.10.16.
//

#ifndef ISA_PROJ_ADDRESSPOOL_H
#define ISA_PROJ_ADDRESSPOOL_H

#include <iostream>
#include <list>
#include <set>
#include <mutex>
#include "MacAddress.h"
#include "Reservation.h"
#include "../BaseObject.h"


using namespace std;

namespace addressing {

    /* static */ class AddressPair : public BaseObject{
        const string _name = "AddressPair";
        bool _isFree;
        IpAddress _address;

    public:
        AddressPair(IpAddress & address);
        void setIsFree(bool isFree);
        bool isFree();

        IpAddress getAddress();
        virtual string toString();
        virtual string getLoggableName();
    };

    class AddressPool : public BaseObject {
        const string _name = "AddressPool";
        list<IpAddress> _reserved;
        list<AddressPair> _addresses;

    public:
        AddressPool(IpAddress& net_address, int prefix,list<IpAddress> & reserved);
        IpAddress getAddress();
        void releaseAddress(IpAddress & addr);

        void printCurrentState();
        virtual string toString();
        virtual string getLoggableName();
    };

}


#endif //ISA_PROJ_ADDRESSPOOL_H
