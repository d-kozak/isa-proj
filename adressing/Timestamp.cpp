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

    Timestamp &Timestamp::operator=(Timestamp other) {
        this->_startTime = other._startTime;
        return *this;
    }

    bool Timestamp::isLeaseExpired() {
        return countSecondsSinceStarted() >= LEASE_TIME;
    }

    string Timestamp::toString() const {
        string s;
        s += this->_name + " -> ";
        s += std::to_string(countSecondsSinceStarted());
        return s;
    }

    string Timestamp::getLoggableName() const  {
        return this->_name;
    }


    int Timestamp::countSecondsSinceStarted() const {
        auto end = std::chrono::system_clock::now();
        auto elapsed = (end - this->_startTime);
        long nanos = elapsed.count();
        long secs = nanos / 1000000000;
        return secs;
    }

    void Timestamp::printTimeInfo() {
        std::time_t now = std::chrono::system_clock::to_time_t(_startTime);
        std::tm now_tm = *std::localtime(&now);

        chrono::system_clock::time_point expireTimePoint = _startTime + std::chrono::seconds(LEASE_TIME);
        std::time_t expireTimeT = std::chrono::system_clock::to_time_t(expireTimePoint);
        std::tm expire_tm = *std::localtime(&expireTimeT);

        std::cout << std::put_time(&now_tm, TIME_FORMAT) << " " << std::put_time(&expire_tm, TIME_FORMAT) << std::endl;
    }

}
