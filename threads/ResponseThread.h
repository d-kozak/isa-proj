#ifndef ISA_PROJ_RESPONSETHREAD_H
#define ISA_PROJ_RESPONSETHREAD_H


#include "../BaseObject.h"
#include "../request/AbstractRequest.h"
#include "../adressing/AddressHandler.h"
#include "CancellableThread.h"
#include "../request/DhcpMessage.h"
#include "ThreadWrapper.h"

using namespace addressing;

/**
 * Thread which was supposed to reply to an accepted DHCP message
 */
class ResponseThread : public ThreadWrapper{
    /**
     * pointer to the request to which the thread should answer
     */
    AbstractRequest* _request;
    /**
     * reference to the handler
     */
    AddressHandler & _addressHandler;
public:
    AddressHandler &get_addressHandler() const;

public:
    /**
     * constructor, parses the message, create the request
     * @return
     */
    ResponseThread(AddressHandler & handler,ProtocolParser & protocol,vector<unsigned char>& msg);
    /**
     * simply starts the reply process by execting method performRequest on the request object
     */
    virtual void run();
};


#endif //ISA_PROJ_RESPONSETHREAD_H
