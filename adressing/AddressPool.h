//
// Declaration of AddressInfo and AddressPool
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
#include "../BaseObject.h"
#include "../exceptions/InvalidArgumentException.h"
#include "Timestamp.h"
#include "IpAddress.h"


using namespace std;
namespace addressing {

    /**
     * This enum specifies the state of ip address in the pool
     * FREE no one uses the address
     * TO_BE_BINDED between DHCPOFFER and DHCPREQUEST, can still be used by somebody else if neccessary
     * BINDED currently in use by someone
     * EXPIRED after its lease finished, but still preferable for the old client if he sends request, can be used by somebody else if necceassary
     * RESERVED cannot be used at alll
     */
    typedef enum {
        FREE, TO_BE_BINDED, BINDED, EXPIRED, RESERVED, DIRECT_MAPPING
    } addressState;

    /**
     * Represents one address in the address pool
     * @see AddressPool
     */
    class AddressInfo : public BaseObject {
        const string _name = "AddressInfo";
        /**
         * state of the address
         */
        addressState _state;

        /**
         * ip address
         */
        IpAddress _address;

        /**
         * mac of the client who is binded to the ip address
         */
        MacAddress *_mac = NULL;

        /**
         * timestamp specifying when the client was binded to the ip address
         */
        Timestamp *_timestamp = NULL;

    public:
        /**
         * constructor, creates new address with the state FREE
         * @param address ip address
         */
        AddressInfo(IpAddress &address) : _address(address), _state(FREE) {}

        /**
         * constructor, creates new address
         * @param address ip address
         * @param state of the address
         */
        AddressInfo(IpAddress &address, addressState state) : _address(address), _state(state) {}

        /**
         * changes the state of address
         * @param newState new state
         * @throw InvalidArgumentException if the state is RESERVED or DIRECT_MAPPING, these states are permanent
         */
        void setState(addressState newState) {
            if (_state == RESERVED || _state == DIRECT_MAPPING) {
                std::stringstream ss;
                ss << "Cannot change state of reserved address: ";
                ss << this->toString();
                throw InvalidArgumentException(ss.str());
            }
            this->_state = newState;
        }

        /**
         * @return state of the address
         */
        addressState getState() { return _state; }

        /**
         * @return ip address
         */
        IpAddress getAddress();

        /**
         * @return pointer to the mac address
         * @warning does not pass ownership, DO NOT CHANGE OR DELETE the object
         */
        MacAddress *getMac();

        /**
         * sets new macAddress, deletes the old if any was set
         * @param mac mac address
         * @warning the method passes the ownership of the object from client code to the pool, DO NOT MODIFY the object directly
         */
        void setMac(MacAddress *mac) {
            if(this->_mac != NULL)
                delete this->_mac;
            this->_mac = mac;
        }

        /**
         * @return current timestamp or NULL if none
         */
        Timestamp *getTimestamp() const;

        /**
         * creates new timestamp, deletes the old one if any was set
         */
        void createTimestamp() {
            if (this->_timestamp != NULL)
                delete this->_timestamp;
            this->_timestamp = new Timestamp;
        }

        /**
         * bins given mac address to the ip addres
         * @param mac address
         * @throws Invalid ArgumentException of the state is invalid(it should hopefully never be)
         */
        void bindTheAddress(MacAddress &mac);

        /**
         * set the state to binded, saves the mac address
         * @param mac
         */
        void markAsToBeBinded(MacAddress &mac);

        virtual string toString() const;

        virtual string getLoggableName() const;

        /**
         * cleans all dynamically allocated stuff
         */
        void clean();

        /**
         * destructor, cleans the Mac and Timestamp pointers if they are set
         */
        virtual ~AddressInfo();
    };

    /**
     * Pool of addresses used by the server, contains methods for getting free address, changing states of address and so on...
     */
    class AddressPool : public BaseObject {
        const string _name = "AddressPool";

        /**
         * reserved ip address, they can never be assigned
         */
        list <IpAddress> _reserved;
        /**
         * list of all addresses in the pool
         * TODO optimize the structure if neccessary
         */
        list <AddressInfo> _addresses;

        /**
         * static assigment from mac to ip
         */
        map<MacAddress, IpAddress> _directMapping;

    public:
        /**
         * constructor,creates the pool
         * @param net_address network address
         * @param reserved list of reserved addresses
         * @param direct_mapping static assigments from mac to ip
         */
        AddressPool(IpAddress &net_address, int prefix, list <IpAddress> &reserved,
                    map<MacAddress, IpAddress> &direct_mapping);

        /**
         * gets the address from the pool
         * @see AddressHandler
         * @param mac address of the client
         * @return address which can be binded for the client
         * @throws OutOfAddressException if no address is available
         */
        IpAddress getAddress(MacAddress &mac);

        /**
         * confirms binding, move the address to BINDED state
         * @see AddressHandler
         * @param addr specified ip address or NULL_IP
         * @param mac client mac address
         * @return info about the binded address
         * @throws InvalidArgumentException if this binding is not possible
         */
        const AddressInfo &confirmBindigFor(IpAddress &addr, MacAddress &mac);

        /**
         * Releases specified address, move its state to FREE
         * NO-OP for non existing bindings
         * @param addr
         */
        void releaseAddress(IpAddress &addr);

        /**
         * Releases specified address, move its state to FREE
         * NO-OP for non existing bindings
         * @param addr
         */
        void releaseAddress(MacAddress &mac);

        /**
         * callled from addressCollector to change to state to expired
         * @see AddressCollector
         * @param addr ip with expired binding
         */
        void addressExpired(IpAddress &addr);

        /**
         * cleans all dynamically allocated stuff
         */
        void clean();

        /**
         * @return list of all adddresses into the pool
         */
        list <AddressInfo> &getAddresses() {
            return _addresses;
        }

        /**
         * prinst the state of object
         */
        void printCurrentState();

        virtual string toString() const;

        virtual string getLoggableName() const;
    };

}


#endif //ISA_PROJ_ADDRESSPOOL_H
