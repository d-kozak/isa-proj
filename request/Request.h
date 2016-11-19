#ifndef ISA_PROJ_REQUEST_H
#define ISA_PROJ_REQUEST_H


#include "AbstractRequest.h"

/**
 * Class represents dhcp Request message
 */
class Request : public AbstractRequest {
    const string _name = "Request";
public:
    Request(DhcpMessage msg):AbstractRequest(msg){}

    /**
     * First check sanity of the mesage, than check if the message is really for this server, then confirm the bindign
     * reply either with ACK or NACK
     * @param handler
     */
    virtual void performTask(AddressHandler & handler);
    virtual string toString() const;
    virtual string getLoggableName() const;
};


#endif //ISA_PROJ_REQUEST_H
