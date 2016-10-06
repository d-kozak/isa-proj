//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_ABSTRACTREQUEST_H
#define ISA_PROJ_ABSTRACTREQUEST_H


#include "../BaseObject.h"

class AbstractRequest : public BaseObject {


public:
    static enum RequestType {
        DISCOVER, OFFER, REQUEST, ACK, NACK, RELEASE
    };

    virtual void handleRequest() = 0;
};


#endif //ISA_PROJ_ABSTRACTREQUEST_H
