//
// Created by david on 6.10.16.
//

#include "ProtocolParser.h"
#include "exceptions/ParseException.h"
#include "request/Discover.h"
#include "request/Request.h"
#include "request/Release.h"

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


vector<char> ProtocolParser::createMsg(AbstractRequest * req){
    DhcpMessage msg;
    return msg.createMessageVector();
}
