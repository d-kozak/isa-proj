//
// Created by david on 11.11.16.
//

#include "Nack.h"
#include "../sockets/Socket.h"

void Nack::performTask(DhcpMessage & msg, IpAddress & addr,AddressHandler & handler){
    AbstractReply::performTask(msg,addr,handler);

    IpAddress nullAdrr  = IpAddress(0,0,0,0);
    msg.setCiaddr(nullAdrr);
    msg.setGiaddr(nullAdrr);
    msg.setSiaddr(nullAdrr);
    msg.setYiaddr(nullAdrr);

    IpAddress broadcast = IpAddress::getBroadcastAddr();
    Socket socket(broadcast);
    vector<unsigned char> vec = msg.createMessageVector();
    socket.sendMessage(vec,broadcast);
}
