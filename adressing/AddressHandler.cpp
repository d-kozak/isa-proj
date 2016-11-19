//
// see header file for comments
//

#include "AddressHandler.h"
#include "../exceptions/InvalidArgumentException.h"
#include <sstream>
#include <unistd.h>

namespace addressing {
    AddressHandler::AddressHandler(IpAddress &net_address, int prefix, list <IpAddress> &reserved,
                                   map<MacAddress, IpAddress> &direct_mapping) :
            _lock(), _pool(net_address, prefix, reserved,direct_mapping),
            _collector(this),_prefix(prefix),_serverAddress(net_address) {}


    IpAddress AddressHandler::getAddressFor(MacAddress &mac) {
        lock_guard<recursive_mutex>(this->_lock);
        IpAddress addr = this->_pool.getAddress(mac);
        return addr;
    }

    const AddressInfo &  AddressHandler::confirmBindingFor(IpAddress & addr,MacAddress & mac){
        lock_guard<recursive_mutex>(this->_lock);
        return this->_pool.confirmBindigFor(addr,mac);
    }

    void AddressHandler::releaseAddress(MacAddress &mac) {
        lock_guard<recursive_mutex>(this->_lock);
        this->_pool.releaseAddress(mac);
    }


    const int AddressHandler::getPrefix() const {
        return this->_prefix;
    }

    void AddressHandler::printCurrentState() {
        cout << this->toString() << endl;
    }

    /**
     * @warning This method is not thread safe
     * the information may be stale
     * @return
     */
    string AddressHandler::toString() const{
        //lock_guard<recursive_mutex>(this->_lock);
        //
        stringstream ss;
        ss << "------------------------------" << endl;
        ss << this->_name << " -> " << endl;
        ss << this->_pool.toString() << endl;
        ss << "}" << endl;
        ss << this->_collector.toString() << endl;
        ss << "------------------------------";
        return ss.str();
    }

    string AddressHandler::getLoggableName() const {
        return this->_name;
    }


    void AddressHandler::start() {
        this->_collector.start();
    }

    void AddressHandler::interrupt() {
        this->_collector.interrupt();
    }

    const IpAddress &AddressHandler::getServerAddress() const {
        return _serverAddress;
    }

    AddressHandler::~AddressHandler(){
        this->_collector.interrupt();
        this->_pool.clean();
    }

    /////////////////////////////////////////////////////////

    AddressCollector::AddressCollector(AddressHandler *ha) : _handler(ha), _garbageCollector(), isInterrupted(false) {}

    void AddressCollector::start() {
        this->_garbageCollector = thread(
                [this] { this->run(); }
        );
    }

    void AddressCollector::interrupt() {
        if(this->isInterrupted) // if the thread is already interrupted, just return
            return;
        this->isInterrupted = true;
        this->_garbageCollector.join();
    }

    void AddressCollector::run() {
        cout << "COLLECTOR STARTED" << endl;
        while (!isInterrupted) {
            lock_guard<recursive_mutex>(this->_handler->_lock);
            // It is not possible to iterate a collection and delete its elemetns at once,
            // thats why we first get the list of items and delete it later
            list <IpAddress> to_expire;
            for (auto &item : this->_handler->_pool.getAddresses()) {
                if (item.getState() == BINDED) {
                    if(item.getTimestamp()->isLeaseExpired()){
                    cout << "COLLECTOR will removing reservation for " << item.getAddress().toString() << endl;
                    to_expire.push_back(item.getAddress());
                }}
            }
            for (auto &x: to_expire) {
                this->_handler->_pool.addressExpired(x);
            }
            sleep(1);
        }
        cout << "COLLECTOR FINISHED" << endl;
    }

    string AddressCollector::toString() const {
        stringstream ss;
        ss << this->_name << " -> ";
        if(isInterrupted)
            ss << "interrupted";
        else
            ss << "running";
        return ss.str();
    }

    string AddressCollector::getLoggableName() const  {
        return this->_name;
    }
}