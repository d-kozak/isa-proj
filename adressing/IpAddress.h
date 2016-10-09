//
// Created by david on 5.10.16.
//

#ifndef ISA_PROJ_IPADDRESS_H
#define ISA_PROJ_IPADDRESS_H

#include <iostream>
#include <netinet/in.h>
#include "../BaseObject.h"

#define ADDRESS_SIZE 4

using namespace std;

namespace addressing {
    class IpAddress : public BaseObject {
        const string _name = "IpAddress";
        unsigned char _parts[ADDRESS_SIZE];
    public:

        IpAddress(string address);
        IpAddress(vector<char> address);
        IpAddress(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

        IpAddress &operator=(IpAddress other);

        IpAddress next_addr();

        IpAddress next_addr(int distance);

        in_addr_t getAddrForSocket();
        string asString();

        bool isBroadcastAddr();

        bool operator<(const IpAddress &other) const;

        bool operator>(const IpAddress &other) const;

        bool operator==(const IpAddress &lhs);

        bool operator!=(const IpAddress &lhs);


        virtual string toString();

        virtual string getLoggableName();

        static IpAddress getBroadcastAddr(){
            IpAddress address(255,255,255,255);
            return address;
        }
    };
}


#endif //ISA_PROJ_IPADDRESS_H
