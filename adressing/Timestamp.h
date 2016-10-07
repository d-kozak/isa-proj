//
// Created by david on 5.10.16.
//

#ifndef ISA_PROJ_TIMESTAMP_H
#define ISA_PROJ_TIMESTAMP_H

#include <iostream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

#include "../BaseObject.h"

using namespace std;

namespace addressing {
    class Timestamp : public BaseObject {
        const string _name = "TimeStamp";
        static const int LEASE_TIME = 3; //1 * 60 * 60;
        chrono::system_clock::time_point _startTime;

        int countSecondsSinceStarted();
    public:
        Timestamp();

        Timestamp &operator=(Timestamp other);
        bool operator==(const Timestamp &rhs);
        bool operator!=(const Timestamp &rhs);
        bool isLeaseExpired();

        virtual string toString();
        virtual string getLoggableName();
    };
}


#endif //ISA_PROJ_TIMESTAMP_H
