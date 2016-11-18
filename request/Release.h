//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_RELEASE_H
#define ISA_PROJ_RELEASE_H


#include "AbstractRequest.h"

class Release : public AbstractRequest {
    const string _name = "Release";
public:
    Release(DhcpMessage msg):AbstractRequest(msg){}
    virtual void performTask(AddressHandler & handler);
    virtual string toString() const;
    virtual string getLoggableName()const;
};


#endif //ISA_PROJ_RELEASE_H
