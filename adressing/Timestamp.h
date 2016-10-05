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
        chrono::system_clock::time_point startTime;

    public:
        Timestamp();

        inline bool operator==(const Timestamp &lhs, const Timestamp &rhs);
        static bool isLeaseExpired();
    };
}


#endif //ISA_PROJ_TIMESTAMP_H
