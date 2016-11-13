//
// Created by david on 6.10.16.
//

#include "Request.h"
#include "Ack.h"
#include "../constants.h"
#include "Nack.h"

void Request::performTask(AddressHandler &handler) {
    MacAddress &mac = _msg.getChaddr();
    IpAddress &ciaddr = _msg.getCiaddr();
    try {
        IpAddress serverAddress = handler.getServerAddress();
        if (serverAddress == _msg.getServerIdentifier()) {
            const AddressInfo &info = handler.confirmBindingFor(ciaddr, mac);
            //<mac_adresa> <ip_addresa> <cas_prideleni_ip_adresy> <cas_vyprseni_prirazeni_adresy>
            std::cout << mac.toString() << " " << ciaddr.toString() << " ";
            info.getTimestamp()->printTimeInfo();

            Ack ack;
            ack.performTask(_msg, ciaddr, handler);
        }
    } catch (BaseException &e) {
        cerr << e.toString() << endl;
        Nack nack;
        nack.performTask(_msg, ciaddr, handler);
    }
}


string Request::toString() {
    return this->_name;
}

string Request::getLoggableName() {
    return this->_name;
}
