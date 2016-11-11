//
// Created by david on 11.11.16.
//

#include "Ack.h"
#include "../sockets/Socket.h"

void Ack::performTask(DhcpMessage & msg, IpAddress & addr,AddressHandler & handler){
    AbstractReply::performTask(msg,addr,handler);
    msg.setCiaddr(addr);

    IpAddress broadcast = IpAddress::getBroadcastAddr();
    Socket socket1(broadcast);
    vector<unsigned char> vec = msg.createMessageVector();
    socket1.sendMessage(vec,broadcast);
}
