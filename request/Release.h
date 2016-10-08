//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_RELEASE_H
#define ISA_PROJ_RELEASE_H


#include "AbstractRequest.h"

class Release : public AbstractRequest {
public:
    virtual void performTask();
    virtual void after();
    virtual string toString();
    virtual string getLoggableName();
};


#endif //ISA_PROJ_RELEASE_H
