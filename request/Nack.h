//
// Created by david on 11.11.16.
//

#ifndef ISA_PROJ_NACK_H
#define ISA_PROJ_NACK_H

#include "AbstractRequest.h"

class Nack : public AbstractReply{
public:
    virtual void performTask(DhcpMessage & msg, IpAddress & addr,AddressHandler & handler);
};

#endif //ISA_PROJ_NACK_H
