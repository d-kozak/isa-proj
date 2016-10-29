//
// Created by david on 5.10.16.
//

#include "MacAddress.h"
#include "../exceptions/ParseException.h"
#include "../exceptions/InvalidArgumentException.h"
#include <string>
#include <sstream>
#include <string.h>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>

namespace addressing {

    MacAddress::MacAddress(string addr) {
        char buf[3];
        buf[2] = '\0';

        int cell_index = 0;
        int i  = 0;

        if(addr.size() != MAC_SIZE * 2 + MAC_SIZE -1 ){
            stringstream ss;
            ss << "Mac address " << addr << "is either too long or too short";
            throw ParseException(ss.str());
        }

        for (char & c : addr){
            if(i == 2){
                if(c != ':'){
                    stringstream ss;
                    ss << "Mac address "  << addr << " is incorrect";
                    throw ParseException(ss.str());
                }
                // now convert hexadecimal string in buffer into a decimal number
                _parts[cell_index] = strtoul(buf, NULL, 16);

                cell_index++;
                i = 0;
            } else {
                buf[i] = c;
                i++;
            }
        }
        _parts[cell_index] = strtoul(buf, NULL, 16);
    }



    MacAddress::MacAddress(unsigned char a, unsigned char b,unsigned  char c,unsigned  char d,unsigned  char e,unsigned  char f){
        this->_parts[0] = a;
        this->_parts[1] = b;
        this->_parts[2] = c;
        this->_parts[3] = d;
        this->_parts[4] = e;
        this->_parts[5] = f;
    }

    MacAddress::MacAddress(unsigned char * addr) {
        for (int i = 0; i < MAC_SIZE; ++i) {
            this->_parts[i] = addr[i];
        }
    }

    MacAddress::MacAddress(vector<unsigned char> addr) {
        if(addr.size() != 6){
            string msg = "Invalid size of MAC addr: ";
            msg += addr.size();
            throw InvalidArgumentException(msg);
        }
        for (unsigned long i = 0; i < MAC_SIZE; ++i) {
            this->_parts[i] = addr.at(i);
        }
    }

    MacAddress &MacAddress::operator=(MacAddress other) {
//        std::swap(_parts[0], other._parts[0]);
//        std::swap(_parts[1], other._parts[1]);
//        std::swap(_parts[2], other._parts[2]);
//        std::swap(_parts[3], other._parts[3]);
        for (int i = 0; i < MAC_SIZE; ++i) {
            this->_parts[i] = other._parts[i];
        }
        return *this;
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
        // MUST BE JUST <, not <= !!!!!!!!
        for (int i = 0; i < MAC_SIZE; ++i) {
            if(this->_parts[i] < other._parts[i])
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

    unsigned char MacAddress::getPart(int index) const {
        if(index < 0 || index > MAC_SIZE -1)
            throw InvalidArgumentException("Invalid index");
        return this->_parts[index];
    }

    string constRefToString(const MacAddress & mac){
        string ret;
        for (int i = 0; i < MAC_SIZE; ++i) {
            std::stringstream sstream;
            sstream << std::hex << (int) mac.getPart(i);
            ret += sstream.str();

            if(i != MAC_SIZE - 1){
                ret += ':';
            }
        }
        return ret;
    }
}
