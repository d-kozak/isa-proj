//
// Created by david on 5.10.16.
//

#include "ctype.h"
#include "IpAddress.h"
#include "../exceptions/ParseException.h"
#include "../exceptions/OutOfAddressException.h"

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
        for (int i = 0; i < distance; ++i) {
            IpAddress address = this->next_addr();
            if (i == distance - 1)
                return address;
        }

        throw OutOfAddressException("IpAddress::next(int) <- executin should never get here");
    }

    bool IpAddress::operator<(const IpAddress &other) const {
        for (int i = 0; i < 4; ++i) {
            if(this->_parts[i] <= other._parts[i])
                return true;
        }
        return false;
    }

    bool IpAddress::operator>(const IpAddress &other) const {
        for (int i = 0; i < 4; ++i) {
            if(this->_parts[i] > other._parts[i])
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
