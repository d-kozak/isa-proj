#ifndef ISA_PROJ_DISCOVER_H
#define ISA_PROJ_DISCOVER_H


#include "AbstractRequest.h"

/**
 * Class represents DHCP discover message
 */
class Discover : public AbstractRequest {
    const string _name = "Discover";
public:
    Discover(DhcpMessage msg):AbstractRequest(msg){}
    /**
     * method checks if there is any address available and if so, it replies with a dhcp offer mesage
     * @param handler
     */
    virtual void performTask(AddressHandler & handler);

    virtual string toString() const;
    virtual string getLoggableName() const;
};


#endif //ISA_PROJ_DISCOVER_H
