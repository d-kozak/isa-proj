//
// Definition of class representing one Mac address
//

#ifndef ISA_PROJ_MACADDRESS_H
#define ISA_PROJ_MACADDRESS_H

#include <iostream>
#include <vector>
#include "../BaseObject.h"

/**
 * size of MAC address in bytes
 */
#define MAC_SIZE 6

using namespace std;

namespace addressing {

    /**
     * Class representing one mac address
     */
    class MacAddress : public BaseObject{
        const string _name = "MacAddress";
        /**
         * internal prepresentation, 6 bytes
         */
        unsigned char _parts[MAC_SIZE];

    public:
        /**
         * constructor, creates the object
         * @param addr
         * @return
         */
        MacAddress(string addr);
        /**
         * constructor, creates the object
         * @param addr
         * @return
         */
        MacAddress(unsigned char a,unsigned  char b,unsigned  char c,unsigned  char d,unsigned  char e,unsigned char f);
        MacAddress(vector<unsigned char> addr);
        /**
         * constructor, creates the object
         * @param addr
         * @return
         */
        MacAddress(unsigned char * addr);

        
        MacAddress &operator=(MacAddress other);

        bool operator==(const MacAddress &lhs);
        bool operator!=(const MacAddress &lhs);
        bool operator<(const MacAddress &other) const;
        bool operator>(const MacAddress &other) const;

        /**
         * @param index index
         * @return return byte at given index
         */
        unsigned char getPart(int index)const ;

        virtual string toString() const ;
        virtual string getLoggableName() const;
    };

    /**
     * creates string representation of given mac address
     * @param mac
     * @return
     */
    string constRefToString(const MacAddress & mac);
}


#endif //ISA_PROJ_MACADDRESS_H
