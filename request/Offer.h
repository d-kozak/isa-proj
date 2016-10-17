//
// Created by david on 17.10.16.
//

#ifndef ISA_PROJ_OFFER_H
#define ISA_PROJ_OFFER_H


#include "AbstractRequest.h"

class Offer : public AbstractRequest {
    const string _name = "Offer";
    IpAddress & _addr;
    AddressHandler & _handler;

public:
    Offer(DhcpMessage & msg, IpAddress & addr,AddressHandler & handler);
    void performTask();

    virtual string toString();
    virtual string getLoggableName();

};


#endif //ISA_PROJ_OFFER_H
