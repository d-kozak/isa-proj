//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_REQUEST_H
#define ISA_PROJ_REQUEST_H


#include "AbstractRequest.h"

class Request : public AbstractRequest {
    const string _name = "Request";
public:
    Request(DhcpMessage msg):AbstractRequest(msg){}
    virtual void performTask(AddressHandler & handler);
    virtual string toString();
    virtual string getLoggableName();
};


#endif //ISA_PROJ_REQUEST_H
