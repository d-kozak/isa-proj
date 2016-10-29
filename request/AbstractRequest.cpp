//
// Created by david on 6.10.16.
//

#include "AbstractRequest.h"
#include "../exceptions/ParseException.h"
#include "Discover.h"
#include "Request.h"
#include "Release.h"

AbstractRequest * ProtocolParser::parseRequest(DhcpMessage & msg){
    AbstractRequest * ret;
    char type = msg.getMeesageType();
    switch(type){
        case DISCOVER:
            ret = new Discover(msg);
            break;
        case REQUEST:
            ret = new Request(msg);
            break;
        case RELEASE:
            ret = new Release(msg);
            break;
        default:
            string res = "Mesage type not recoqnized : ";
            res += type;
            throw ParseException(res);

    }
    return ret;
}

