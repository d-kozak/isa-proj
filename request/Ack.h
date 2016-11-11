//
// Created by david on 11.11.16.
//

#ifndef ISA_PROJ_ACK_H
#define ISA_PROJ_ACK_H

#include "AbstractRequest.h"

class Ack : public AbstractReply{
public:
    virtual void performTask(DhcpMessage & msg, IpAddress & addr,AddressHandler & handler);
};

#endif //ISA_PROJ_ACK_H
