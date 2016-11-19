//
// see header for comments
//

#include "Nack.h"
#include "../sockets/Socket.h"

void Nack::performTask(DhcpMessage & msg, IpAddress & addr,AddressHandler & handler){
    AbstractReply::performTask(msg,addr,handler);

    IpAddress NULL_IP(0,0,0,0);
    msg.setCiaddr(NULL_IP);
    msg.setGiaddr(NULL_IP);
    msg.setSiaddr(NULL_IP);
    msg.setYiaddr(NULL_IP);
    msg.setMeesageType(NACK);

    IpAddress broadcast = IpAddress::getBroadcastAddr();
    Socket socket(broadcast);
    vector<unsigned char> vec = msg.createMessageVector();
    socket.sendMessage(vec,broadcast);
}
