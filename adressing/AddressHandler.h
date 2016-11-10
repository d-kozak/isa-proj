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

    class AddressHandler;

    class AddressCollector  : public BaseObject {
        const string _name = "AddressCollector";
        thread _garbageCollector;
        AddressHandler * _handler;

        volatile bool isInterrupted;

        void run();

    public:
        AddressCollector(AddressHandler * ha);
        void start();
        void interrupt();

        virtual string toString();
        virtual string getLoggableName();
    };

    class AddressHandler : public BaseObject {
        const string _name = "AddressHandler";
        recursive_mutex _lock;
        AddressPool _pool;
        AddressCollector _collector;

        const int _prefix;
        const IpAddress serverAddress;


        friend class AddressCollector;

//        bool findReservation(MacAddress & mac);
    public:
        AddressHandler(IpAddress& net_address, int prefix,list<IpAddress> & reserved,map<MacAddress,IpAddress> &direct_mapping);
        IpAddress getAddressFor(MacAddress & mac);
        void releaseAddress(MacAddress & mac);
        void printCurrentState();

        void confirmBindingFor(IpAddress & addr,MacAddress & mac);

        const int getPrefix() const;

        virtual string toString();
        virtual string getLoggableName();

        void start();
        void interrupt();

        const int get_prefix() const;

        const IpAddress &getServerAddress() const;
    };
}


#endif //ISA_PROJ_ADDRESSHANDLER_H
