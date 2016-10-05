//
// Created by david on 5.10.16.
//

#include "MacAddress.h"

namespace addressing {
    inline bool MacAddress::operator==(const MacAddress &lhs, const MacAddress &rhs){
        for (int i = 0; i < MAC_SIZE; ++i) {
            if(lhs.parts[i] != rhs.parts[i])
                return false;
        }
        return true;
    }

    MacAddress::MacAddress(string address){}
    MacAddress::MacAddress(char a, char b, char c, char d, char e, char f){}
    bool MacAddress::operator<(const MacAddress &other) const{}
    bool MacAddress::operator>(const MacAddress &other) const{}
}
