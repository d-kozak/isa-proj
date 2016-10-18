//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_ABSTRACTREQUEST_H
#define ISA_PROJ_ABSTRACTREQUEST_H


#include "../BaseObject.h"
#include "../adressing/IpAddress.h"
#include "../adressing/MacAddress.h"
#include "../request/DhcpMessage.h"
#include "../threads/ResponseThread.h"


enum BOOTPTYPE{
    BOOT_REQUEST = 1,
    BOOT_REPLY = 2
};

enum RequestType {
    DISCOVER=1, OFFER=2, REQUEST=3, ACK=5, NACK=6, RELEASE=7
};

class AbstractRequest : public BaseObject {
    friend class ProtocolParser;

    virtual void performTask(ResponseThread & thread) = 0;

protected:
    DhcpMessage _msg;

public:
    void handleRequest(ResponseThread & thread);

    void setMsg(const DhcpMessage &msg);
};


class AbstractReply : public BaseObject {
    friend class ProtocolParser;
public:
    virtual void performTask(DhcpMessage & msg, IpAddress & addr,AddressHandler & handler) = 0;
};


#endif //ISA_PROJ_ABSTRACTREQUEST_H
