//
// Created by david on 8.10.16.
//

#include "DhcpMessage.h"
#include <arpa/inet.h>


#define getDataTypeFromCharVec(dataType, charVec, index) (*((dataType *) (&charVec[index])))
#define getElemAsType(type, vec, index) *((type *)(&vec[index]))

void appendToVec(vector<unsigned char> &vec, unsigned char *source, int size) {
    for (int i = 0; i < size; ++i) {
        vec.push_back(source[i]);
    }
}

void appendToVec(vector<unsigned char> &destination, addressing::IpAddress &addr) {
    vector<unsigned char> from = addr.asVector();
    destination.insert(destination.end(), from.begin(), from.end());
}

void check_size_of_option(unsigned char real_size, unsigned char expected_size) {
    if (real_size != expected_size) {
        stringstream ss;
        ss << "Wrong size of option... " << real_size << " vs " << expected_size;
        throw ParseException(ss.str());
    }
}


DhcpMessage::DhcpMessage(vector<unsigned char> &msg) : ciaddr(0, 0, 0, 0), yiaddr(0, 0, 0, 0), siaddr(0, 0, 0, 0),
                                                       giaddr(0, 0, 0, 0), chaddr(0, 0, 0, 0, 0, 0),
                                                       subnetMask(0, 0, 0, 0),
                                                       serverIdentifier(0, 0, 0, 0) {

    if (msg.size() < MSG_SIZE_WITH_OPTIONS) {
        stringstream ss;
        ss << "Message is too short" << msg.data();
        throw ParseException(ss.str());
    }


    this->op = msg[_op];
    this->htype = msg[_htype];
    this->hlen = msg[_hlen];
    this->hops = msg[_hops];


    this->xid = ntohl(getDataTypeFromCharVec(uint32_t, msg, _xid));
    this->secs = ntohs(getDataTypeFromCharVec(uint16_t, msg, _secs));
    this->flags = ntohs(getDataTypeFromCharVec(uint16_t, msg, _flags));

    // todo check if this tranformation of ip address really works... :X
    this->ciaddr = addressing::IpAddress(msg.data() + _ciaddr);
    this->yiaddr = addressing::IpAddress(msg.data() + _yiaddr);
    this->siaddr = addressing::IpAddress(msg.data() + _siaddr);
    this->giaddr = addressing::IpAddress(msg.data() + _giaddr);
    this->chaddr = addressing::MacAddress(msg.data() + _chaddr);
    memcpy(this->sname, msg.data() + _sname, _size_sname);
    memcpy(this->file, msg.data() + _file, _size_file);


// now parse options
    int index = _options;
    unsigned char opId;

//first check magic cookies 99, 130, 83 and 99
    if (msg[index] != 99 || msg[index + 1] != 130 || msg[index + 2] != 83 || msg[index + 3] != 99) {
        stringstream ss;
        ss << "Invalid magic cookies" << endl;
        throw ParseException(ss.str());
    }

    index += 4;

    if (index >= msg.size()) {
        throw ParseException("Invalid size of dhcp message");
    }


    while ((opId = msg[index]) != end) {
        switch (opId) {
            case subnetMaskID: {
                check_size_of_option(msg[index + 1], _size_subnet_mask);
                index += 2;
                this->subnetMask = addressing::IpAddress(msg.data() + index);
                break;
            }
            case leaseTimeID: {
                check_size_of_option(msg[index + 1], _size_lease_time);
                index += 2;
                unsigned char *ptr = (unsigned char *) &leaseTime;
                for (int j = 0; j < _size_lease_time; ++j) {
                    ptr[j] = msg[index + j];
                }
                break;
            }
            case messageTypeID: {
                check_size_of_option(msg[index + 1], _size_message_type);
                index += 2;
                this->messageType = msg[index];
                break;
            }
            case serverIdentifierID: {
                check_size_of_option(msg[index + 1], _size_server_identifier);
                index += 2;
                this->serverIdentifier = addressing::IpAddress(msg.data() + index);
                break;
            }
            default: {
                stringstream ss;
                ss << "Unknown option id: " << (int) opId;
                throw ParseException(ss.str());
            }
        }
        if (index >= msg.size()) {
            throw ParseException("Invalid size of dhcp message");
        }
        index++;
    }

}

DhcpMessage &DhcpMessage::operator=(DhcpMessage other) {
    this->setOp(other.getOP());
    this->setHType(other.getHtype());
    this->setHLen(other.getHlen());
    this->setHOps(other.getHOps());
    this->setXid(other.getXid());
    this->setSecs(other.getSecs());
    this->setFlags(other.getFlags());
    this->setCiaddr(other.getCiaddr());
    this->setYiaddr(other.getYiaddr());
    this->setSiaddr(other.getSiaddr());
    this->setGiaddr(other.getGiaddr());
    this->setChaddr(other.getChaddr());
    this->setSname(other.getSname());
    this->setFile(other.getFile());
    this->setMeesageType(other.getMeesageType());
    this->setLeaseTime(other.getLeaseTime());
    this->setSubnetMask(other.getSubnetMask());
    return *this;
}

vector<unsigned char> DhcpMessage::createMessageVector() {
    vector<unsigned char> ret;
    ret.resize(MSG_SIZE_WITH_OPTIONS);
    ret[_op] = op;
    ret[_htype] = htype;
    ret[_hlen] = hlen;
    ret[_hops] = hops;
    getElemAsType(uint32_t, ret, _xid) = htonl(xid);
    getElemAsType(uint16_t, ret, _secs) = htons(secs);
    getElemAsType(uint16_t, ret, _flags) = htons(flags);

    getElemAsType(uint32_t, ret, _ciaddr) = htonl(ciaddr.getAddrForSocket());
    getElemAsType(uint32_t, ret, _yiaddr) = htonl(yiaddr.getAddrForSocket());
    getElemAsType(uint32_t, ret, _siaddr) = htonl(siaddr.getAddrForSocket());
    getElemAsType(uint32_t, ret, _giaddr) = htonl(giaddr.getAddrForSocket());

    appendToVec(ret, sname, _size_sname);
    appendToVec(ret, file, _size_file);


    ret[_options] = 99;
    ret[_options] = 130;
    ret[_options] = 83;
    ret[_options] = 99;

    // todo finish the rest of this method


    ret.push_back(subnetMaskID);
    ret.push_back(_size_subnet_mask);
    appendToVec(ret, subnetMask);

    ret.push_back(leaseTimeID);
    ret.push_back(_size_lease_time);
    appendToVec(ret, (unsigned char *) &leaseTime, 4);

    ret.push_back(messageTypeID);
    ret.push_back(_size_message_type);
    ret.push_back(messageType);

    ret.push_back(serverIdentifierID);
    ret.push_back(_size_server_identifier);
    appendToVec(ret, serverIdentifier);

    ret.push_back(end);
    ret.push_back(_size_end);
    return ret;
}


string DhcpMessage::toString() {
    stringstream ss;
    ss << this->_name + " -> " << "{" << endl;
    ss << this->createMessageVector().data() << endl;
    ss << "}";
    return ss.str();
}
