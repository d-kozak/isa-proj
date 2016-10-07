//
// Created by david on 5.10.16.
//

#include "Reservation.h"

namespace addressing{
    Reservation::Reservation(IpAddress & ipAddress1,Timestamp & timestamp1): _ipAddress(ipAddress1),_timestamp(timestamp1){}

    Reservation &Reservation::operator=(Reservation other){
        this->_ipAddress = other._ipAddress;
        this->_timestamp = other._timestamp;
    }

    string Reservation::toString(){
        string ret;
        ret += this->_name;
        ret += " -> {(" + this->_ipAddress.toString() + ")(" + this->_timestamp.toString() + ")}";
        return ret;
    }

    string Reservation::getLoggableName(){
        return this->_name;
    }

    IpAddress Reservation::getIpAddress(){
        return this->_ipAddress;
    }

    Timestamp Reservation::getTimestamp(){
        return this->_timestamp;
    }
}
