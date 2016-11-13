//
// Created by david on 17.10.16.
//

#include "Offer.h"
#include "../sockets/Socket.h"
#include "../constants.h"
#include "Nack.h"

void Offer::performTask(DhcpMessage &_msg, IpAddress &_addr, AddressHandler &_handler) {
    AbstractReply::performTask(_msg, _addr, _handler);
    IpAddress broadcast = IpAddress::getBroadcastAddr();
    Socket socket1(broadcast);
    _msg.setYiaddr(_addr);
    _msg.setMeesageType(OFFER);


    vector<unsigned char> msg = _msg.createMessageVector();
    socket1.sendMessage(msg, broadcast);
}

string Offer::toString() {
    return this->_name;
}

string Offer::getLoggableName() {
    return this->_name;
}
