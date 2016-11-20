//
// see header for comments
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
        IpAddress serverIdentifier = _msg.getServerIdentifier(); // server idenfier = client specifies which server he wants to use
        if (serverAddress ==  serverIdentifier || serverIdentifier == NULL_IP) {
            AddressInfo &info = handler.confirmBindingFor(ciaddr, mac);
            //<mac_adresa> <ip_addresa> <cas_prideleni_ip_adresy> <cas_vyprseni_prirazeni_adresy>

            IpAddress givenAddress = info.getAddress();
            std::cout << mac.toString() << " " << givenAddress.toString() << " ";
            info.getTimestamp()->printTimeInfo();

            Ack ack;
            ack.performTask(_msg, givenAddress, handler);
        } else {
            std::stringstream ss;
            std::string serverIdOption = _msg.getServerIdentifier().toString();
            ss << "Request for somebody else " << serverIdOption << std::endl;
            std:: cout << ss.str();
        }
    } catch (BaseException &e) {
        cerr << e.toString() << endl;
        Nack nack;
        nack.performTask(_msg, ciaddr, handler);
    }
}


string Request::toString() const {
    return this->_name;
}

string Request::getLoggableName() const {
    return this->_name;
}
