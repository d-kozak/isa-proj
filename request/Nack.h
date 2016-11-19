#ifndef ISA_PROJ_NACK_H
#define ISA_PROJ_NACK_H

#include "AbstractRequest.h"

/**
 * class represents DHCP NACK messages
 */
class Nack : public AbstractReply{
    const string _name = "Nack";
public:
    /**
     * Basically just sets all fields to zero in this case
     */
    virtual void performTask(DhcpMessage & msg, IpAddress & addr,AddressHandler & handler);
    virtual string toString() const{
        return this->_name;
    }

    virtual string getLoggableName() const{
        return this->_name;
    }
};

#endif //ISA_PROJ_NACK_H
