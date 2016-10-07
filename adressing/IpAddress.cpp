//
// Created by david on 5.10.16.
//

#include "ctype.h"
#include "IpAddress.h"
#include "../exceptions/ParseException.h"

namespace addressing {

    IpAddress::IpAddress(string  address){
        char buf [4];
        buf[3]= '\0';
        int buf_index = 0;
        int cell_index = 0;

        int index = 0;
        int item;
        for(unsigned long i = 0 ; i < address.size() ; i++){
            item = address.at(i);
            if(buf_index == 3 && item != '.')
                throw ParseException("Parse Error");

            if(!isdigit(item)){
                if('.' == item){
                    for (int j = buf_index; j < 3 ; ++j) {
                        buf[j] = '\0';
                    }

                    _parts[cell_index] = (unsigned char) atoi(buf);
                    cell_index++;
                    if(cell_index > 3){
                        throw ParseException("Parse Error");
                    }
                    buf_index = 0;
                } else{
                    throw ParseException("Parse Error");
                };
            } else {
                buf[buf_index] = item;
                buf_index++;
            }
            index++;
        }

        // add last number
        for (int j = buf_index; j < 3 ; ++j) {
            buf[j] = '\0';
        }

        _parts[cell_index] = (unsigned char) atoi(buf);
    }
    IpAddress::IpAddress(unsigned char a,unsigned char b,unsigned  char c,unsigned char d){
        this->_parts[0] = a;
        this->_parts[1] = b;
        this->_parts[2] = c;
        this->_parts[3] = d;
    }



    bool IpAddress::operator==(const IpAddress &lhs) {
        for (int i = 0; i < ADDRESS_SIZE; ++i) {
            if (this->_parts[i] != lhs._parts[i])
                return false;
        }
        return true;
    }

    bool IpAddress::operator!=(const IpAddress &lhs){
        return !operator==(lhs);
    }

    string IpAddress::toString(){
        string ret;
        ret.append(this->_name);
        ret.append(" -> ");
        ret.append((char*)this->_parts,4);
    }

    string IpAddress::getLoggableName(){
        return this->_name;
    }
}
