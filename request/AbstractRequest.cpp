//
// Created by david on 6.10.16.
//

#include "AbstractRequest.h"
#include "../exceptions/ParseException.h"
#include "Discover.h"
#include "Request.h"
#include "Release.h"
#include "../constants.h"

AbstractRequest * ProtocolParser::parseRequest(DhcpMessage & msg){
    AbstractRequest * ret;
    unsigned char type = msg.getMeesageType();
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
    cleanPtrIfSet();
    this->req = ret;
    return ret;
}

void AbstractReply::performTask(DhcpMessage & msg, IpAddress & addr,AddressHandler & handler){
    msg.setOp(BOOT_REPLY);
    msg.setServerIdentifier(handler.getServerAddress());
    IpAddress netmask = IpAddress::getNetMaskFor(handler.get_prefix());
    msg.setSubnetMask(netmask);
    msg.setLeaseTime(LEASE_TIME);
}


ProtocolParser::~ProtocolParser(){
    cleanPtrIfSet();
}

void ProtocolParser::cleanPtrIfSet(){
    if(req != nullptr)
        delete req;
}



AbstractRequest::~AbstractRequest(){

}

AbstractReply::~AbstractReply(){

}