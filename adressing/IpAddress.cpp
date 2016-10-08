//
// Created by david on 5.10.16.
//

#include <sstream>

#include "ctype.h"
#include "IpAddress.h"
#include "../exceptions/ParseException.h"
#include "../exceptions/OutOfAddressException.h"
#include "../exceptions/InvalidArgumentException.h"

namespace addressing {

    IpAddress::IpAddress(string address) {
        char buf[4];
        buf[3] = '\0';
        int buf_index = 0;
        int cell_index = 0;

        int index = 0;
        int item;
        for (unsigned long i = 0; i < address.size(); i++) {
            item = address.at(i);
            if (buf_index == 3 && item != '.')
                throw ParseException("Parse Error");

            if (!isdigit(item)) {
                if ('.' == item) {
                    for (int j = buf_index; j < 3; ++j) {
                        buf[j] = '\0';
                    }

                    _parts[cell_index] = (unsigned char) atoi(buf);
                    cell_index++;
                    if (cell_index > 3) {
                        throw ParseException("Parse Error");
                    }
                    buf_index = 0;
                } else {
                    throw ParseException("Parse Error");
                };
            } else {
                buf[buf_index] = item;
                buf_index++;
            }
            index++;
        }

        // add last number
        for (int j = buf_index; j < 3; ++j) {
            buf[j] = '\0';
        }

        _parts[cell_index] = (unsigned char) atoi(buf);
    }

    IpAddress::IpAddress(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
        this->_parts[0] = a;
        this->_parts[1] = b;
        this->_parts[2] = c;
        this->_parts[3] = d;
    }

    in_addr_t IpAddress::getAddrForSocket(){
        in_addr_t ret;

        in_addr_t first = _parts[0];
        in_addr_t second = _parts[1];
        in_addr_t third = _parts[2];
        in_addr_t fourth = _parts[3];

        ret ^= ret;
        ret = (first << 24) | (second << 16) | (third << 8) | fourth;
        return ret;
    }

    string IpAddress::asString(){
        stringstream ss;
        ss << std::to_string((int) this->_parts[0]) << ".";
        ss << std::to_string((int) this->_parts[1]) << ".";
        ss << std::to_string((int) this->_parts[2]) << ".";
        ss << std::to_string((int) this->_parts[3]);
        return ss.str();
    }


    IpAddress &IpAddress::operator=(IpAddress other) {
        std::swap(_parts[0], other._parts[0]);
        std::swap(_parts[1], other._parts[1]);
        std::swap(_parts[2], other._parts[2]);
        std::swap(_parts[3], other._parts[3]);
        return *this;
    }

    IpAddress IpAddress::next_addr() {
        IpAddress address(_parts[0], _parts[1], _parts[2], _parts[3]);
        if (address._parts[3] < 255)
            address._parts[3] += 1;
        else {
            address._parts[3] = 0;
            if (address._parts[2] < 255)
                address._parts[2] += 1;
            else {
                address._parts[2] = 0;
                if (address._parts[1] < 255) {
                    address._parts[1] += 1;
                } else {
                    address._parts[1] = 0;
                    if (address._parts[0] < 255)
                        address._parts[0] += 1;
                    else
                        throw OutOfAddressException("No next for 255.255.255.255");
                }
            }
        }
        return address;
    }

    IpAddress IpAddress::next_addr(int distance) {
        if(distance < 1)
            throw InvalidArgumentException("Param distance cannot be less then 1");
        IpAddress address = *this;
        for (int i = 0; i < distance; ++i) {
            address=address.next_addr();
            if (i == distance - 1)
                return address;
        }

        throw OutOfAddressException("IpAddress::next(int) <- executin should never get here");
    }

    bool IpAddress::isBroadcastAddr(){
        return this->operator==(IpAddress::BroadcastAddress);
    }

    bool IpAddress::operator<(const IpAddress &other) const {
        for (int i = 0; i < 4; ++i) {
            if (this->_parts[i] <= other._parts[i])
                return true;
        }
        return false;
    }

    bool IpAddress::operator>(const IpAddress &other) const {
        for (int i = 0; i < 4; ++i) {
            if (this->_parts[i] > other._parts[i])
                return true;
        }
        return false;
    }


    bool IpAddress::operator==(const IpAddress &lhs) {
        for (int i = 0; i < ADDRESS_SIZE; ++i) {
            if (this->_parts[i] != lhs._parts[i])
                return false;
        }
        return true;
    }

    bool IpAddress::operator!=(const IpAddress &lhs) {
        return !operator==(lhs);
    }

    string IpAddress::toString() {
        string ret;
        ret.append(this->_name);
        ret.append(" -> ");
        for (int i = 0; i < 4; ++i) {
            ret += std::to_string((int) this->_parts[i]);
            if (i != 3)
                ret += '.';
        }
        return ret;
    }

    string IpAddress::getLoggableName() {
        return this->_name;
    }
}
