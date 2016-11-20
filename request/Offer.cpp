//
// see header for comments
//
#include "Offer.h"
#include "../sockets/Socket.h"
#include "../constants.h"

extern volatile Socket *sock;

void Offer::performTask(DhcpMessage &_msg, IpAddress &_addr, AddressHandler &_handler) {
    AbstractReply::performTask(_msg, _addr, _handler);
    _msg.setYiaddr(_addr);
    _msg.setMeesageType(OFFER);


    vector<unsigned char> msg = _msg.createMessageVector();
    sock->broadcastMessage(msg);
}

string Offer::toString() const {
    return this->_name;
}

string Offer::getLoggableName() const {
    return this->_name;
}
