//
// Created by david on 11.11.16.
//

#ifndef ISA_PROJ_ACK_H
#define ISA_PROJ_ACK_H

#include "AbstractRequest.h"

class Ack : public AbstractReply{
    const string _name = "Ack";
public:
    virtual void performTask(DhcpMessage & msg, IpAddress & addr,AddressHandler & handler);
    virtual string toString(){
        return this->_name;
    }

    virtual string getLoggableName(){
        return this->_name;
    }
};

#endif //ISA_PROJ_ACK_H
