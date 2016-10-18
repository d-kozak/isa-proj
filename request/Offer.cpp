//
// Created by david on 17.10.16.
//

#include "Offer.h"
#include "../sockets/Socket.h"

void Offer::performTask(DhcpMessage & _msg, IpAddress & _addr,AddressHandler & _handler) {
    unsigned char * ptr;
    IpAddress broadcast = IpAddress::getBroadcastAddr();
    Socket socket1(broadcast);

    ptr = _msg.getItem(_msg.op);
    *ptr = BOOT_REPLY;

    ptr = _msg.getItem(_msg.ciaddr);
    memset(ptr,'\0',_msg.size_iaddr);

    // do not know any other server, set zero for now
    // TODO maybe collect info about other servers as well?
    ptr = _msg.getItem(_msg.siaddr);
    memcpy(ptr,'\0',_msg.size_iaddr);

    vector<unsigned char> newAddr = _addr.asVector();
    ptr = _msg.getItem(_msg.yiaddr);
    memcpy(ptr,newAddr.data(),ADDRESS_SIZE);

    ptr = _msg.getItem(_msg.message_type);
    *ptr = OFFER;

    ptr = _msg.getItem(_msg.lease_time);
    memcpy(ptr,&Timestamp::LEASE_TIME,_msg.size_lease_time);

    ptr = _msg.getItem(_msg.subnestMask);
    const int prefix = _handler.getPrefix();
    memcpy(ptr,&prefix,_msg.size_subnet_mask);

    // TODO set end option ? (what is that? )

    vector<unsigned char> msg = _msg.createMessageVector();
    socket1.sendMessage(msg,broadcast);
}

string Offer::toString(){
    return this->_name;
}

string Offer::getLoggableName(){
    return this->_name;
}
