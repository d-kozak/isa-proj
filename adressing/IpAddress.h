//
// Definition of class modelling one IP address
//

#ifndef ISA_PROJ_IPADDRESS_H
#define ISA_PROJ_IPADDRESS_H

#include <iostream>
#include <netinet/in.h>
#include "../BaseObject.h"
#include <vector>

#define ADDRESS_SIZE 4

using namespace std;

namespace addressing {
    /**
     * class for one IP address
     */
    class IpAddress : public BaseObject {
        const string _name = "IpAddress";
        /**
         * ip address is represented as 4 separate bytes
         */
        unsigned char _parts[ADDRESS_SIZE];

        /**
         * inits the address from string
         * @throws ParseException if the format is invalid
         * @param address
         */
        void initAddressFromString(string address);
    public:
        /**
         * constructor, creates the object
         * @param address
         * @return
         */
        IpAddress(string address);
        /**
         * constructor, creates the object
         * @param address
         * @return
         */
        IpAddress(vector<unsigned char> address);
        IpAddress(char* address);
        /**
         * constructor, creates the object
         * @param address
         * @return
         */
        IpAddress(int address);
        /**
         * constructor, creates the object
         * @param address
         * @return
         */
        IpAddress(unsigned char a, unsigned char b, unsigned char c, unsigned char d);
        /**
         * constructor, creates the object
         * @param address
         * @return
         */
        IpAddress(unsigned char* mem);


        IpAddress &operator=(IpAddress other);

        /**
         * @returns next address (ip adrr++)
         */
        IpAddress next_addr();

        /**
         * @param distance
         * @return n-th(distance-nth) address
         */
        IpAddress next_addr(int distance);

        /**
         * @return the address in the form if one int
         */
        uint32_t getAddrForSocket() const ;
        string asString() const ;

        /**
         * @return the address for vector
         */
        vector<unsigned char> asVector();

        /**
         * @return true if the address if broadcast, false otherwise
         */
        bool isBroadcastAddr();

        bool operator<(const IpAddress &other) const;

        bool operator>(const IpAddress &other) const;

        bool operator==(const IpAddress &lhs);

        bool operator!=(const IpAddress &lhs);


        virtual string toString() const ;

        virtual string getLoggableName() const ;

        /**
         * returns broadcast address
         * @return
         */
        static IpAddress getBroadcastAddr(){
            IpAddress address(255,255,255,255);
            return address;
        }

        /**
         * creates IpAddress representing netmask for given prefix
         * @param prefix
         * @return netmask
         */
        static IpAddress getNetMaskFor(int prefix){
            int address = INT32_MAX;
            int zeroBytes = 32 - prefix;
            address <<= zeroBytes;
            return IpAddress (address);
        }
    };
}


#endif //ISA_PROJ_IPADDRESS_H
