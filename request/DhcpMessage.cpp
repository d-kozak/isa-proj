//
// Created by david on 8.10.16.
//

#include "DhcpMessage.h"
#include <arpa/inet.h>


#define getDataTypeFromCharVec(dataType, charVec, index) (*((dataType *) (&charVec[index])))
#define getElemAsType(type, vec, index) *((type *)(&vec[index]))


void check_size_of_option(unsigned char realSize, unsigned char expectedSize, unsigned long currentIndex,
                          unsigned long sizeOfMsg) {
    if (realSize != expectedSize) {
        stringstream ss;
        ss << "Wrong size of option... " << realSize << " vs " << expectedSize;
        throw ParseException(ss.str());
    }
    unsigned long minimalPossibleSize = currentIndex + 1 + 1 + expectedSize;
    if (minimalPossibleSize > sizeOfMsg) {
        stringstream ss;
        ss << "Wrong size of message " << realSize << " vs at least " << minimalPossibleSize;
        throw ParseException(ss.str());
    }
}


DhcpMessage::DhcpMessage(vector<unsigned char> &msg) : ciaddr(0, 0, 0, 0), yiaddr(0, 0, 0, 0), siaddr(0, 0, 0, 0),
                                                       giaddr(0, 0, 0, 0), chaddr(0, 0, 0, 0, 0, 0),
                                                       subnetMask(0, 0, 0, 0),
                                                       serverIdentifier(0, 0, 0, 0) {

    if (msg.size() < MSG_SIZE) {
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
    unsigned long index = _options;
    unsigned char opId;

    if (msg.size() < MSG_SIZE + MAGIC_COOKIES_SIZE) {
        // message does not contain any options...
        return;
    }

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
        if (msg[index] == pad) // skip pads
            continue;

        // check if we can read at leat option id and option size
        if (index + 1 >= msg.size()) {
            throw ParseException("Invalid size of dhcp message");
        }

        switch (opId) {
            case subnetMaskID: {
                check_size_of_option(msg[index + 1], _size_subnet_mask, index, msg.size());
                index += 2;
                this->subnetMask = addressing::IpAddress(msg.data() + index);
                index += _size_subnet_mask;
                break;
            }
            case leaseTimeID: {
                check_size_of_option(msg[index + 1], _size_lease_time, index, msg.size());
                index += 2;
                this->leaseTime = ntohl(getDataTypeFromCharVec(uint32_t,msg,index));
                index += _size_lease_time;
                break;
            }
            case messageTypeID: {
                check_size_of_option(msg[index + 1], _size_message_type, index, msg.size());
                index += 2;
                this->messageType = msg[index];
                index += _size_message_type;
                break;
            }
            case serverIdentifierID: {
                check_size_of_option(msg[index + 1], _size_server_identifier, index, msg.size());
                index += 2;
                this->serverIdentifier = addressing::IpAddress(msg.data() + index);
                index += _size_server_identifier;
                break;
            }
            default: {
                stringstream ss;
                ss << "Unknown option id: " << (int) opId;
                index += 2 + msg[index+1]; // 2 for option
            }
        }
        if (index >= msg.size()) {
            throw ParseException("Invalid size of dhcp message");
        }
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
    this->setServerIdentifier(other.getServerIdentifier());
    return *this;
}

vector<unsigned char> DhcpMessage::createMessageVector() const {
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


    memcpy(ret.data() + _sname,sname,_size_sname);
    memcpy(ret.data() + _file,file,_size_file);

    int index = _options;
    // magic cookies
    ret[index++] = 99;
    ret[index++] = 130;
    ret[index++] = 83;
    ret[index++] = 99;


    // now options
    ret[index++] = subnetMaskID;
    ret[index++] = _size_subnet_mask;
    getElemAsType(uint32_t,ret,index) = htonl(subnetMask.getAddrForSocket());
    index += _size_subnet_mask;

    ret[index++] = leaseTimeID;
    ret[index++] = _size_lease_time;
    getElemAsType(uint32_t,ret,index) = htonl(leaseTime);
    index += _size_lease_time;

    ret[index++] = messageTypeID;
    ret[index++] = _size_message_type;
    ret[index++] = messageType;

    ret[index++] = serverIdentifierID;
    ret[index++] = _size_server_identifier;
    getElemAsType(uint32_t,ret,index) = htonl(serverIdentifier.getAddrForSocket());
    index += _size_server_identifier;

    ret[index++] = end; // type
    ret[index++] = end; // size  TODO probably not neccessary

    return ret;
}


string DhcpMessage::toString()  const {
    stringstream ss;
    ss << this->_name + " -> " << "{" << endl;
    ss << this->createMessageVector().data() << endl;
    ss << "}";
    return ss.str();
}
