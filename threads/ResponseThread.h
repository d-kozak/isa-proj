//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_RESPONSETHREAD_H
#define ISA_PROJ_RESPONSETHREAD_H


#include "../BaseObject.h"
#include "../request/AbstractRequest.h"
#include "../adressing/AddressHandler.h"
#include "CancellableThread.h"
#include "../request/DhcpMessage.h"

using namespace addressing;

class ResponseThread : public CancellableThread{
    AbstractRequest* _request;
    AddressHandler & _addressHandler;
public:
    AddressHandler &get_addressHandler() const;

public:
    ResponseThread(AddressHandler & handler,ProtocolParser & protocol,vector<unsigned char>& msg);
    void performTask();
};


#endif //ISA_PROJ_RESPONSETHREAD_H
