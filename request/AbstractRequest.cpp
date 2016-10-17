//
// Created by david on 6.10.16.
//

#include "AbstractRequest.h"
#include "../threads/ResponseThread.h"

void AbstractRequest::handleRequest(ResponseThread & thread){
    this->performTask(thread);
    this->after();
}

void AbstractRequest::setMsg(const DhcpMessage &msg) {
    AbstractRequest::msg = msg;
}
