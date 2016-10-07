//
// Created by david on 5.10.16.
//

#ifndef ISA_PROJ_RESERVATION_H
#define ISA_PROJ_RESERVATION_H

#include <iostream>

#include "IpAddress.h"
#include "Timestamp.h"
#include "../BaseObject.h"

namespace addressing{

class Reservation : public BaseObject{
    const std::string _name = "Reservation";
public:
    IpAddress _ipAddress;
    Timestamp _timestamp;
    Reservation(IpAddress & ipAddress1,Timestamp & timestamp1);

    virtual string toString();
    virtual string getLoggableName();
};

}


#endif //ISA_PROJ_RESERVATION_H
