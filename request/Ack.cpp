//
// see header for comments
//

#include "Ack.h"
#include "../sockets/Socket.h"

extern volatile Socket *sock;

void Ack::performTask(DhcpMessage & msg, IpAddress & addr,AddressHandler & handler){
    AbstractReply::performTask(msg,addr,handler);
    msg.setYiaddr(addr);
    msg.setMeesageType(ACK);

    vector<unsigned char> vec = msg.createMessageVector();
    sock->broadcastMessage(vec);
}
