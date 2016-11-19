#ifndef ISA_PROJ_RELEASE_H
#define ISA_PROJ_RELEASE_H


#include "AbstractRequest.h"

/**
 * Class represents DHCP release message
 */
class Release : public AbstractRequest {
    const string _name = "Release";
public:
    Release(DhcpMessage msg):AbstractRequest(msg){}

    /**
     * just iforms the pool about address being released, does not perform reply
     */
    virtual void performTask(AddressHandler & handler);

    virtual string toString() const;
    virtual string getLoggableName()const;
};


#endif //ISA_PROJ_RELEASE_H
