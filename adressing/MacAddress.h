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
        const string _name = "MacAddress";
        unsigned char _parts[MAC_SIZE];

    public:
        MacAddress(unsigned char a,unsigned  char b,unsigned  char c,unsigned  char d,unsigned  char e,unsigned char f);

        bool operator==(const MacAddress &lhs);
        bool operator!=(const MacAddress &lhs);
        bool operator<(const MacAddress &other) const;
        bool operator>(const MacAddress &other) const;

        virtual string toString();
        virtual string getLoggableName();
    };

}


#endif //ISA_PROJ_MACADDRESS_H
