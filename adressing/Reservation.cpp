//
// Created by david on 5.10.16.
//

#include "Reservation.h"

namespace addressing{
    Reservation::Reservation(IpAddress & ipAddress1,Timestamp & timestamp1): _ipAddress(ipAddress1),_timestamp(timestamp1){}

    string Reservation::toString(){
        string ret;
        ret += this->_name;
        ret += " -> {(" + this->_ipAddress.toString() + ")(" + this->_timestamp.toString() + ")}";
        return ret;
    }

    string Reservation::getLoggableName(){
        return this->_name;
    }
}
