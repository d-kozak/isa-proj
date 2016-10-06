//
// Created by david on 5.10.16.
//

#ifndef ISA_PROJ_IPADDRESS_H
#define ISA_PROJ_IPADDRESS_H

#include <iostream>
#include "../BaseObject.h"

#define ADDRESS_SIZE 4

using namespace std;

namespace addressing {
    class IpAddress : public BaseObject {
        const char _parts[ADDRESS_SIZE];

    public:
        IpAddress(string address);
        IpAddress(char a, char b, char c, char d);
        inline bool operator==(const IpAddress &lhs, const IpAddress &rhs);
    };
}


#endif //ISA_PROJ_IPADDRESS_H
