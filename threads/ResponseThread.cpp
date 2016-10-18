//
// Created by david on 6.10.16.
//

#include "ResponseThread.h"

ResponseThread::ResponseThread(AddressHandler & handler,ProtocolParser & protocol,vector<unsigned char>& msg):_addressHandler(handler){
    DhcpMessage dhcpMessage(msg);
    AbstractRequest* req = protocol.parseRequest(dhcpMessage);
    this->_request = req;
}

void ResponseThread::performTask(){
    this->_request->performTask(_addressHandler);
    this->interrupt();
}

AddressHandler &ResponseThread::get_addressHandler() const {
    return _addressHandler;
}
