#ifndef ISA_PROJ_ACK_H
#define ISA_PROJ_ACK_H

#include "AbstractRequest.h"

/**
 * Class representing DHCP message ACK
 */
class Ack : public AbstractReply{
    const string _name = "Ack";
public:
    /**
     * In this case the reply just calls superclass version of performTask and then add ciaddr field and message type
     * params are self explanatory
     * @param msg
     * @param addr
     * @param handler
     */
    virtual void performTask(DhcpMessage & msg, IpAddress & addr,AddressHandler & handler);
    virtual string toString() const {
        return this->_name;
    }

    virtual string getLoggableName() const{
        return this->_name;
    }
};

#endif //ISA_PROJ_ACK_H
