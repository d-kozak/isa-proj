//
// Created by david on 17.10.16.
//

#ifndef ISA_PROJ_OFFER_H
#define ISA_PROJ_OFFER_H


#include "AbstractRequest.h"

class Offer : public AbstractReply {
    const string _name = "Offer";
public:
    Offer(){}
    virtual void performTask(DhcpMessage & msg, IpAddress & addr,AddressHandler & handler);

    virtual string toString() const ;
    virtual string getLoggableName() const ;
    ~Offer(){}
};


#endif //ISA_PROJ_OFFER_H
