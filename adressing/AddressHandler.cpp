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
            _collector(*this) {}


    IpAddress AddressHandler::getAddressFor(MacAddress &mac) {
        lock_guard<recursive_mutex>(this->_lock);

        // first check if the address is not already there
        auto item = this->_reservations.find(mac);
        if(item != this->_reservations.end())
            return (*item).second.getIpAddress();

        IpAddress addr = this->_pool.getAddress();
        Timestamp stamp;
        Reservation reservation(addr,stamp);
//        this->_reservations[mac] = reservation;
        this->_reservations.emplace(mac,reservation);
        return addr;
    }

bool AddressHandler::findReservation(MacAddress &mac, MacAddress** ptr) {
        lock_guard<recursive_mutex>(this->_lock);
        for (auto x : this->_reservations) {
            if (mac == x.first) {
                *ptr = (MacAddress*) &x.first;
                return true;
            }
        }
        return false;
    }

    void AddressHandler::releaseAddress(MacAddress &mac) {
        lock_guard<recursive_mutex>(this->_lock);
        MacAddress* tmp;
        if (this->findReservation(mac,&tmp)) {
            this->_reservations.erase(*tmp);
        } else {
            throw InvalidArgumentException("Mac address " + mac.toString() + " is not a part of any known reservation");
        }
    }

    void AddressHandler::printCurrentState() {
        cout << this->toString();
    }

    string AddressHandler::toString() {
        lock_guard<recursive_mutex>(this->_lock);
        stringstream ss;
        ss << "------------------------------" << endl;
        ss << this->_name << " -> " << endl;
        ss << this->_pool.toString() << endl;
        ss << this->_collector.toString();
        ss << "------------------------------" << endl;
        return ss.str();
    }

    string AddressHandler::getLoggableName() {
        return this->_name;
    }


    void AddressHandler::start(){
        this->_collector.start();
    }
    void AddressHandler::interrupt(){
        this->_collector.interrupt();
    }

    /////////////////////////////////////////////////////////

    AddressCollector::AddressCollector(AddressHandler &ha) : _handler(ha), _garbageCollector(), isInterrupted(false) {}

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
        while (!isInterrupted) {
            cout << "collector running" << endl;
                lock_guard<recursive_mutex>(this->_handler._lock);
                for(auto & item : this->_handler._reservations){
                    if(item.second.getTimestamp().isLeaseExpired()) {
                        MacAddress tmp = item.first;
                        this->_handler.releaseAddress(tmp);
                    }
                }

            cout << "collector finished" << endl;
            sleep(1);
        }
    }

    string AddressCollector::toString(){
        stringstream ss;
        ss << this->_name << " -> " << this->isInterrupted ? "interrupted" : "running";
        return ss.str();
    }

    string AddressCollector::getLoggableName() {
        return this->_name;
    }
}