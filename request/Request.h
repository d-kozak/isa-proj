//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_REQUEST_H
#define ISA_PROJ_REQUEST_H


#include "AbstractRequest.h"

class Request : public AbstractRequest {
public:
    virtual void handleRequest();
    virtual string toString();
    virtual string getLoggableName();
};


#endif //ISA_PROJ_REQUEST_H
