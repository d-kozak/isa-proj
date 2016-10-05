//
// Created by david on 5.10.16.
//

#include "Timestamp.h"

namespace addressing {
    Timestamp::Timestamp() {}
    inline bool Timestamp::operator==(const Timestamp &lhs, const Timestamp &rhs);
    static bool Timestamp::isLeaseExpired();
}
