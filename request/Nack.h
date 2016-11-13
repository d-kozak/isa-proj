//
// Created by david on 11.11.16.
//

#ifndef ISA_PROJ_NACK_H
#define ISA_PROJ_NACK_H

#include "AbstractRequest.h"

class Nack : public AbstractReply{
    const string _name = "Nack";
public:
    virtual void performTask(DhcpMessage & msg, IpAddress & addr,AddressHandler & handler);
    virtual string toString(){
        return this->_name;
    }

    virtual string getLoggableName(){
        return this->_name;
    }
};

#endif //ISA_PROJ_NACK_H
