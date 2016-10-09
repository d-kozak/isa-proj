//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_ABSTRACTREQUEST_H
#define ISA_PROJ_ABSTRACTREQUEST_H


#include "../BaseObject.h"
#include "../adressing/IpAddress.h"
#include "../adressing/MacAddress.h"
#include "../request/DhcpMessage.h"

class AbstractRequest : public BaseObject {
    friend class ProtocolParser;

    virtual void performTask() = 0;
    virtual void after() = 0;

protected:
    addressing::IpAddress _serverIp;
    addressing::IpAddress _clientIP;
    addressing::MacAddress _clientMac;
    DhcpMessage msg;

public:
    static enum RequestType {
        DISCOVER=1, OFFER=2, REQUEST=3, ACK=5, NACK=6, RELEASE=7
    };

    void handleRequest();
};


#endif //ISA_PROJ_ABSTRACTREQUEST_H
