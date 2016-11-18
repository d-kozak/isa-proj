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
#include "../constants.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

using namespace std;

namespace addressing {
    class Timestamp : public BaseObject {
        const string _name = "TimeStamp";
        const char* TIME_FORMAT = "%Y-%m-%d_%H:%M";
        chrono::system_clock::time_point _startTime;


    public:
        Timestamp();

        Timestamp &operator=(Timestamp other);
        bool operator==(const Timestamp &rhs);
        bool operator!=(const Timestamp &rhs);
        bool isLeaseExpired();
        int countSecondsSinceStarted() const ;
        void printTimeInfo();
        virtual string toString() const ;
        virtual string getLoggableName() const ;
    };
}


#endif //ISA_PROJ_TIMESTAMP_H
