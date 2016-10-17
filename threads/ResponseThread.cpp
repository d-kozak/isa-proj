//
// Created by david on 6.10.16.
//

#include "ResponseThread.h"

ResponseThread::ResponseThread(AddressHandler & handler,AbstractRequest * request):_addressHandler(handler),_request(request){}

void ResponseThread::performTask(){
    this->_request->handleRequest(*this);
    this->interrupt();
}

AddressHandler &ResponseThread::get_addressHandler() const {
    return _addressHandler;
}
