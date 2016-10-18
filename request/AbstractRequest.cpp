//
// Created by david on 6.10.16.
//

#include "AbstractRequest.h"
#include "../exceptions/ParseException.h"
#include "Discover.h"
#include "Request.h"
#include "Release.h"

void AbstractRequest::setMsg(const DhcpMessage &msg) {
    this->_msg = msg;
}

AbstractRequest * ProtocolParser::parseRequest(DhcpMessage & msg){
    AbstractRequest * ret;
    int type = (int)(*msg.getItem(msg.message_type));
    switch(type){
        case DISCOVER:
            ret = new Discover();
            break;
        case REQUEST:
            ret = new Request();
            break;
        case RELEASE:
            ret = new Release();
            break;
        default:
            string res = "Mesage type not recoqnized : ";
            res += type;
            throw ParseException(res);

    }
    ret->setMsg(msg);
    return ret;
}


vector<unsigned char> ProtocolParser::createMsg(AbstractRequest * req){
    DhcpMessage msg;
    return msg.createMessageVector();
}
