//
// Created by david on 6.10.16.
//

#include "AbstractRequest.h"

void AbstractRequest::handleRequest(ResponseThread & thread){
    this->performTask(thread);
}

void AbstractRequest::setMsg(const DhcpMessage &msg) {
    this->_msg = msg;
}

