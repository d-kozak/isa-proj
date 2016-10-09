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
    ResponseThread(AddressHandler & handler,AbstractRequest * request);
    void performTask();
};


#endif //ISA_PROJ_RESPONSETHREAD_H
