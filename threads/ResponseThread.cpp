//
// see header for details
//

#include "ResponseThread.h"

ResponseThread::ResponseThread(AddressHandler & handler,ProtocolParser & protocol,vector<unsigned char>& msg):_addressHandler(handler){
    DhcpMessage dhcpMessage(msg);
    AbstractRequest* req = protocol.parseRequest(dhcpMessage);
    this->_request = req;
}

void ResponseThread::run(){
    this->_request->performTask(_addressHandler);
}

AddressHandler &ResponseThread::get_addressHandler() const {
    return _addressHandler;
}
