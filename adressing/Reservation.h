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
public:
    const IpAddress ipAddress;
    const Timestamp timestamp;
    Reservation(IpAddress & ipAddress1,Timestamp & timestamp1);
};

}


#endif //ISA_PROJ_RESERVATION_H
