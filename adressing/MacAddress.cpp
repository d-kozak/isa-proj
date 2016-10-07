//
// Created by david on 5.10.16.
//

#include "MacAddress.h"
#include <string>
#include <sstream>

namespace addressing {

    MacAddress::MacAddress(unsigned char a, unsigned char b,unsigned  char c,unsigned  char d,unsigned  char e,unsigned  char f){
        this->_parts[0] = a;
        this->_parts[1] = b;
        this->_parts[2] = c;
        this->_parts[3] = d;
        this->_parts[4] = e;
        this->_parts[5] = f;
    }

    bool MacAddress::operator==(const MacAddress &lhs){
        for (int i = 0; i < MAC_SIZE; ++i) {
            if(this->_parts[i] != lhs._parts[i])
                return false;
        }
        return true;
    }

//    bool MacAddress::operator==(const MacAddress &lhs,MacAddress &rhs){
//        for (int i = 0; i < MAC_SIZE; ++i) {
//            if(lhs._parts[i] != rhs._parts[i])
//                return false;
//        }
//        return true;
//    }

    bool MacAddress::operator!=(const MacAddress &lhs){
        return !operator==(lhs);
    }


    bool MacAddress::operator<(const MacAddress &other) const{
        for (int i = 0; i < MAC_SIZE; ++i) {
            if(this->_parts[i] <= other._parts[i])
                return true;
        }
        return false;
    }
    bool MacAddress::operator>(const MacAddress &other) const{
        for (int i = 0; i < MAC_SIZE; ++i) {
            if(this->_parts[i] > other._parts[i])
                return true;
        }
        return false;
    }


    string MacAddress::getLoggableName(){
        return this->_name;
    }

    string MacAddress::toString(){
        string ret;
        ret.append(this->_name);
        ret.append(" -> ");
        for (int i = 0; i < MAC_SIZE; ++i) {
            std::stringstream sstream;
            sstream << std::hex << (int) this->_parts[i];
            ret += sstream.str();

            if(i != MAC_SIZE - 1){
                ret += ':';
            }
        }
        return ret;
    }
}
