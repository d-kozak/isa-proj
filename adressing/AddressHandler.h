//
// Created by david on 5.10.16.
//

#ifndef ISA_PROJ_ADDRESSHANDLER_H
#define ISA_PROJ_ADDRESSHANDLER_H

#include <iostream>
#include <map>
#include <mutex>
#include <thread>

#include "MacAddress.h"
#include "IpAddress.h"
#include "Reservation.h"
#include "AddressPool.h"
#include "../BaseObject.h"

using namespace std;

namespace addressing {

    class AddressHandler : public BaseObject {
        mutex _lock;
        map<MacAddress,Reservation> _reservations;
        map<MacAddress,IpAddress> _directMapping;
        AddressPool _pool;
        AddressCollector _collector;

    public:
        AddressHandler(IpAddress& first, int prefix,set<IpAddress> & reserved);
        IpAddress getAddressFor(MacAddress & mac);
        void releaseAddress(MacAddress & mac);

    };


    class AddressCollector  : public BaseObject {
        thread garbageCollector;
        AddressHandler & handler;

    public:
        AddressCollector(AddressHandler & ha);
        void start();
        void interrupt();
        ~AddressCollector();
    };

}


#endif //ISA_PROJ_ADDRESSHANDLER_H
