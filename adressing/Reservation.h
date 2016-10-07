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
    IpAddress _ipAddress;
    Timestamp _timestamp;
public:
    Reservation(IpAddress & ipAddress1,Timestamp & timestamp1);

    Reservation &operator=(Reservation other);

    virtual string toString();
    virtual string getLoggableName();

    IpAddress getIpAddress();
    Timestamp getTimestamp();
};

}


#endif //ISA_PROJ_RESERVATION_H
