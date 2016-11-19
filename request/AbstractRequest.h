#ifndef ISA_PROJ_ABSTRACTREQUEST_H
#define ISA_PROJ_ABSTRACTREQUEST_H


#include "../BaseObject.h"
#include "../adressing/IpAddress.h"
#include "../adressing/MacAddress.h"
#include "../request/DhcpMessage.h"
#include "../adressing/AddressHandler.h"

using namespace addressing;

/**
 * Base class for all DHCP requests(messages from client to server) - DISCOVER,REQUEST,RELEASE
 */
class AbstractRequest : public BaseObject {
    friend class ProtocolParser;

protected:
    /**
     * the message where the actual data are stored
     */
    DhcpMessage _msg;

public:
    /**
     * constructor, creates the object
     * @param msg dhcp message
     */
    AbstractRequest(DhcpMessage &msg):_msg(msg){}

    /**
     * Pure virtual method that each request subtype has to implement, it contains the logic of the specific request
     * @param handler addressHandler
     */
    virtual void performTask(AddressHandler & handler) = 0;
    /**
     * Destructor, denoted as pure virtual to make it impossible for client code to instantiate this class
     */
    virtual ~AbstractRequest() = 0;
};


/**
 * Base class for all DHCP replies(messages from server to client) - OFFER,ACK,NACK
 */
class AbstractReply : public BaseObject {
    friend class ProtocolParser;
public:
    /**
     * Pure virtual method that each reply subtype has to implement, it contains the logic of the specific reply
     * INFO: this method is actually implemented in this class  and it contains the changes in dhcp message the every reply does has to do
     * subclasses should call this method in the beginning of their implementation of the method
     * @param handler addressHandler
     */
    virtual void performTask(DhcpMessage & msg, IpAddress & addr,AddressHandler & handler) = 0;

    /**
     * Destructor, denoted as pure virtual to make it impossible for client code to instantiate this class
     */
    virtual ~AbstractReply() = 0;

};


using namespace std;

/**
 * Class which parses the protocol, creates instance of abstractReuqest subtype
 * It also serves as a simple gc, holding reference to a single dynamically allocated request and deleting it in the destructor
 */
class ProtocolParser {
    // pointer to created request so that it will be deleted automatically when protocol parser's destructor is called
    AbstractRequest * req;
    /**
     * deletes the dynamically allocated request if set
     */
    void cleanPtrIfSet();
public:
    /**
     * Constuctor, creates the object
     * @return
     */
    ProtocolParser():req(nullptr){}

    /**
     * parses requets type from the DHCP message
     * @param dhcp_msg message
     * @return pointer to the request
     * @warning does not pass ownership DO NOT DELETE THE OBJECT YOURSELVES
     */
    AbstractRequest * parseRequest(DhcpMessage &dhcp_msg);

    /**
     * Desctructor, cleans the pointer if the request is currently allocated
     */
    ~ProtocolParser();
};


#endif //ISA_PROJ_ABSTRACTREQUEST_H
