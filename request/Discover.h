//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_DISCOVER_H
#define ISA_PROJ_DISCOVER_H


#include "AbstractRequest.h"

class Discover : public AbstractRequest {
    const string _name = "Discover";
public:
    virtual void performTask();
    virtual void after();
    virtual string toString();
    virtual string getLoggableName();
};


#endif //ISA_PROJ_DISCOVER_H
