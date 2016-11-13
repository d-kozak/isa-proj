//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_ABSTRACTREQUEST_H
#define ISA_PROJ_ABSTRACTREQUEST_H


#include "../BaseObject.h"
#include "../adressing/IpAddress.h"
#include "../adressing/MacAddress.h"
#include "../request/DhcpMessage.h"
#include "../adressing/AddressHandler.h"

using namespace addressing;

enum BOOTPTYPE{
    BOOT_REQUEST = 1,
    BOOT_REPLY = 2
};

enum RequestType {
    DISCOVER=1, OFFER=2, REQUEST=3, ACK=5, NACK=6, RELEASE=7
};

class AbstractRequest : public BaseObject {
    friend class ProtocolParser;

protected:
    DhcpMessage _msg;

public:
    AbstractRequest(DhcpMessage &msg):_msg(msg){}
    virtual void performTask(AddressHandler & handler) = 0;
    virtual ~AbstractRequest() = 0;
};


class AbstractReply : public BaseObject {
    friend class ProtocolParser;
public:
    virtual void performTask(DhcpMessage & msg, IpAddress & addr,AddressHandler & handler) = 0;

    virtual ~AbstractReply() = 0;

};


using namespace std;

class ProtocolParser {
    // pointer to created request so that it will be deleted automatically when protocol parser's destructor is called
    AbstractRequest * req;
    void cleanPtrIfSet();
public:
    ProtocolParser():req(nullptr){}
    AbstractRequest * parseRequest(DhcpMessage &dhcp_msg);

    ~ProtocolParser();
};


#endif //ISA_PROJ_ABSTRACTREQUEST_H
