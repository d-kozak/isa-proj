//
// Created by david on 5.10.16.
//

#include "IpAddress.h"

namespace addressing {

    IpAddress::IpAddress(string address){}
    IpAddress::IpAddress(char a, char b, char c, char d){}

    inline bool IpAddress::operator==(const IpAddress &lhs, const IpAddress &rhs) {
        for (int i = 0; i < ADDRESS_SIZE; ++i) {
            if (lhs.parts[i] != rhs.parts[i])
                return false;
        }
        return true;
    }
}
