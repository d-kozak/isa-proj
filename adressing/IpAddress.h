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
        const string _name = "IpAddress";
        unsigned char _parts[ADDRESS_SIZE];

    public:
        IpAddress(string address);
        IpAddress(unsigned char a,unsigned char b,unsigned char c,unsigned char d);


        IpAddress next_addr();
        IpAddress next_addr(int distance);

        bool operator<(const IpAddress &other) const;
        bool operator>(const IpAddress &other) const;
        bool operator==(const IpAddress &lhs);
        bool operator!=(const IpAddress &lhs);



        virtual string toString();
        virtual string getLoggableName();
    };
}


#endif //ISA_PROJ_IPADDRESS_H
