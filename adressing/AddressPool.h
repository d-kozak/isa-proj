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

    class AddressPool : public BaseObject {
        set<IpAddress> _reserved;
        list<AddressPair> _addresses;

        AddressPool(IpAddress& first, int prefix,set<IpAddress> & reserved);

    };


    static class AddressPair : public BaseObject{
        bool _isFree;
        const IpAddress _address;

    public:
        AddressPair(IpAddress & address);
        void setIsFree(bool isFree);
        bool isFree();
        IpAddress getAddress();
    };
}


#endif //ISA_PROJ_ADDRESSPOOL_H
