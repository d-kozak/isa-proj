//
// Created by david on 5.10.16.
//

#include "Timestamp.h"
#include "../constants.h"

namespace addressing {
    Timestamp::Timestamp() : _startTime(std::chrono::system_clock::now()) {}


    bool Timestamp::operator==(const Timestamp &rhs) {
        return this->_startTime == rhs._startTime;
    }

    bool Timestamp::operator!=(const Timestamp &rhs) {
        return !operator==(rhs);
    }

    Timestamp &Timestamp::operator=(Timestamp other){
        this->_startTime = other._startTime;
        return *this;
    }

    bool Timestamp::isLeaseExpired() {
        return countSecondsSinceStarted() >= LEASE_TIME;
    }

    string Timestamp::toString() {
        string s;
        s += this->_name + " -> ";
        s += std::to_string(countSecondsSinceStarted());
        return s;
    }

    string Timestamp::getLoggableName() {
        return this->_name;
    }


    int Timestamp::countSecondsSinceStarted(){
        auto end = std::chrono::system_clock::now();
        auto elapsed = (end - this->_startTime);
        long nanos = elapsed.count();
        long secs = nanos / 1000000000;
        return secs;
    }

}
