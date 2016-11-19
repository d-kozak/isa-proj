//
// Declaration of addressHandler and addressCollector
//

#ifndef ISA_PROJ_ADDRESSHANDLER_H
#define ISA_PROJ_ADDRESSHANDLER_H

#include <iostream>
#include <map>
#include <mutex>
#include <thread>

#include "MacAddress.h"
#include "IpAddress.h"
#include "AddressPool.h"
#include "../BaseObject.h"

using namespace std;

namespace addressing {

    class AddressHandler;

    /**
     * This class periodically traverses list of all addressInfo objects and sets their state to EXPIRED if their lease is expired
     */
    class AddressCollector  : public BaseObject {
        const string _name = "AddressCollector";
        /*
         * the thread that actually does the work
         */
        thread _garbageCollector;

        /**
         * reference to the handler, through which the pool is accessed
         */
        AddressHandler * _handler;

        /**
         * interrupt flag
         */
        volatile bool _isInterrupted;

        /**
         * flag set in start and checked in the interrupt so that we do not try to interrupt something that is not running
         */
        bool _collectorStarted;

        /**
         * main working method of the thread, perodically treaverses the list and and changes addressInfo state if the lease expired
         */
        void run();

    public:
        /**
         * constructor
         * @param ha pointer to the AddressHandler, which should be perodically cleaned
         */
        AddressCollector(AddressHandler * ha);

        /**
         * statrs the underlying thread
         */
        void start();

        /**
         * interrupts the uderlying thread
         */
        void interrupt();

        virtual string toString() const ;
        virtual string getLoggableName() const ;
    };

    /**
     * Adapter allowing easy communication with the adrress pool and its perodical cleaning done by addressCollector
     * Its main purpose is to add trhead safety for the underlying pool
     */
    class AddressHandler : public BaseObject {
        const string _name = "AddressHandler";
        /**
         * mutex which serializes accesses to the object
         */
        recursive_mutex _lock;

        /**
         * pool of available addresses
         */
        AddressPool _pool;

        /**
         * collector whose job is to clean the pool periodically
         */
        AddressCollector _collector;

        /**
         * prefix of the network whose adresses the server handles
         */
        const int _prefix;

        /**
         * address of the server itself, the first address in the list given in constructor
         */
        const IpAddress _serverAddress;


        friend class AddressCollector;

    public:
        /**
         * constructor
         * @param net_address address of the network
         * @param reserved list of reserved addresses
         * @param direct_mapping statically assigned addresss
         */
        AddressHandler(IpAddress& net_address, int prefix,list<IpAddress> & reserved,map<MacAddress,IpAddress> &direct_mapping);

        /**
         * Tries to get an ip address for given mac address
         * @see Discover
         * @param mac address of the client
         * @throws OutOfAddressException if no usable address was found
         * @return address to be offered
         */
        IpAddress getAddressFor(MacAddress & mac);

        /**
         * @see Release
         * Releases ip address for given mac address
         * empty operation if the client has no assigned ip
         * @param mac
         */
        void releaseAddress(MacAddress & mac);

        /**
         * prints info about current state of the object
         */
        void printCurrentState();


        /**
         * @see Request
         * @param addr ip address which the client wants
         * @param mac mac address of the client
         * @throws InvalidArgumentException if the the server cannot give any address to the client
         * @return info about the successfully assigned address
         */
        const AddressInfo & confirmBindingFor(IpAddress & addr,MacAddress & mac);


        virtual string toString() const ;
        virtual string getLoggableName() const ;

        /**
         * starts the address collector
         */
        void startTheAddressCollector();

        /**
         * interrupts the address collector
         */
        void interruptTheAddressCollector();

        /**
         * @return returns prefix of the network
         */
        const int getPrefix() const;

        /**
         * @return the server address
         */
        const IpAddress &getServerAddress() const;

        /**
         * @return the subnet mask
         */
        const IpAddress &getSubnetMask() const;

        ~AddressHandler();
    };
}


#endif //ISA_PROJ_ADDRESSHANDLER_H
