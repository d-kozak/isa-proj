//
// Created by david on 6.10.16.
//

#include "AbstractRequest.h"

void AbstractRequest::handleRequest(){
    this->performTask();
    this->after();
}

void AbstractRequest::setMsg(const DhcpMessage &msg) {
    AbstractRequest::msg = msg;
}
