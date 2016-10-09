//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_ABSTRACTREQUEST_H
#define ISA_PROJ_ABSTRACTREQUEST_H


#include "../BaseObject.h"
#include "../adressing/IpAddress.h"
#include "../adressing/MacAddress.h"
#include "../request/DhcpMessage.h"


enum RequestType {
    DISCOVER=1, OFFER=2, REQUEST=3, ACK=5, NACK=6, RELEASE=7
};

class AbstractRequest : public BaseObject {
    friend class ProtocolParser;

    virtual void performTask() = 0;
    virtual void after() = 0;

protected:
    DhcpMessage msg;

public:


    void handleRequest();

    void setMsg(const DhcpMessage &msg);
};


#endif //ISA_PROJ_ABSTRACTREQUEST_H
