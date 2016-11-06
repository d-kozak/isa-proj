//
// Created by david on 17.10.16.
//

#include "Offer.h"
#include "../sockets/Socket.h"
#include "../constants.h"

void Offer::performTask(DhcpMessage & _msg, IpAddress & _addr,AddressHandler & _handler) {
    IpAddress broadcast = IpAddress::getBroadcastAddr();
    Socket socket1(broadcast);

    _msg.setOp(BOOT_REPLY);
    _msg.setYiaddr(_addr);
    _msg.setLeaseTime(LEASE_TIME);
    _msg.setServerIdentifier(_handler.getServerAddress());
    _msg.setSubnetMask(IpAddress::getNetMaskFor(_handler.get_prefix()));

    vector<unsigned char> msg = _msg.createMessageVector();
    socket1.sendMessage(msg,broadcast);
}

string Offer::toString(){
    return this->_name;
}

string Offer::getLoggableName(){
    return this->_name;
}
