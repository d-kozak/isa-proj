//
// Created by david on 5.10.16.
//

#ifndef ISA_PROJ_MACADDRESS_H
#define ISA_PROJ_MACADDRESS_H

#include <iostream>
#include "../BaseObject.h"

#define MAC_SIZE 6

using namespace std;

namespace addressing {

    class MacAddress : public BaseObject{
        const char parts[MAC_SIZE];

    public:
        MacAddress(string address);
        MacAddress(char a, char b, char c, char d, char e, char f);

        inline bool operator==(const MacAddress &lhs, const MacAddress &rhs);
        bool operator<(const MacAddress &other) const;
        bool operator>(const MacAddress &other) const;
    };

}


#endif //ISA_PROJ_MACADDRESS_H
