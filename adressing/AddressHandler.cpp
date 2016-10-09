//
// Created by david on 5.10.16.
//

#include "AddressHandler.h"
#include "../exceptions/InvalidArgumentException.h"
#include <sstream>
#include <unistd.h>

namespace addressing {
    AddressHandler::AddressHandler(IpAddress &net_address, int prefix, list <IpAddress> &reserved,
                                   map<MacAddress, IpAddress> &direct_mapping) :
            _lock(), _reservations(), _directMapping(direct_mapping), _pool(net_address, prefix, reserved),
            _collector(this) {}


    IpAddress AddressHandler::getAddressFor(MacAddress &mac) {
        lock_guard<recursive_mutex>(this->_lock);

        // first check if the address is not already there
        auto item = this->_reservations.find(mac);
        if (item != this->_reservations.end())
            return (*item).second.getIpAddress();

        IpAddress addr = this->_pool.getAddress();
        Timestamp stamp;
        Reservation reservation(addr, stamp);
//        this->_reservations[mac] = reservation;
        this->_reservations.emplace(mac, reservation);
        return addr;
    }

    void AddressHandler::releaseAddress(MacAddress &mac) {
        lock_guard<recursive_mutex>(this->_lock);
        auto item = this->_reservations.find(mac);
        if (item != this->_reservations.end()) {
            IpAddress toClean = (*item).second.getIpAddress();
            this->_pool.releaseAddress(toClean);
            this->_reservations.erase(item);
        } else {
            throw InvalidArgumentException("Mac address " + mac.toString() + " is not a part of any known reservation");
        }
    }

    void AddressHandler::printCurrentState() {
        cout << this->toString() << endl;
    }

    string AddressHandler::toString() {
        lock_guard<recursive_mutex>(this->_lock);
        stringstream ss;
        ss << "------------------------------" << endl;
        ss << this->_name << " -> " << endl;
        ss << this->_pool.toString() << endl;
        ss << "Static mapping -> {" << endl;
        for (auto & elem : this->_directMapping){
            ss << "\t" << constRefToString(elem.first) << " => " << elem.second.asString() << endl;
        }
        ss << "}" << endl;
        ss << this->_collector.toString() << endl;
        ss << "------------------------------";
        return ss.str();
    }

    string AddressHandler::getLoggableName() {
        return this->_name;
    }


    void AddressHandler::start() {
        this->_collector.start();
    }

    void AddressHandler::interrupt() {
        this->_collector.interrupt();
    }

    /////////////////////////////////////////////////////////

    AddressCollector::AddressCollector(AddressHandler *ha) : _handler(ha), _garbageCollector(), isInterrupted(false) {}

    void AddressCollector::start() {
        this->_garbageCollector = thread(
                [this] { this->run(); }
        );
    }

    void AddressCollector::interrupt() {
        this->isInterrupted = true;
        this->_garbageCollector.join();
    }

    void AddressCollector::run() {
        cout << "COLLECTOR STARTED" << endl;
        while (!isInterrupted) {
            lock_guard<recursive_mutex>(this->_handler->_lock);
            // It is not possible to iterate a collection and delete its elemetns at once,
            // thats why we first get the list of items and delete it later
            list <MacAddress> to_release;
            for (auto &item : this->_handler->_reservations) {
                if (item.second.getTimestamp().isLeaseExpired()) {
                    cout << "COLLECTOR will removing reservation for " << item.second.getIpAddress().toString() << endl;
                    MacAddress tmp = item.first;
                    to_release.push_back(tmp);
                }
            }
            for (auto &x: to_release) {
                this->_handler->releaseAddress(x);
            }
            sleep(1);
        }
        cout << "COLLECTOR FINISHED" << endl;
    }

    string AddressCollector::toString() {
        stringstream ss;
        ss << this->_name << " -> ";
        if(isInterrupted)
            ss << "interrupted";
        else
            ss << "running";
        return ss.str();
    }

    string AddressCollector::getLoggableName() {
        return this->_name;
    }
}