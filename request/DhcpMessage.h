//
// Created by david on 8.10.16.
//

#ifndef ISA_PROJ_DHCPMESSAGE_H
#define ISA_PROJ_DHCPMESSAGE_H

#include <iostream>

#include <sys/types.h>
#include <vector>
#include <sstream>
#include <string.h>
#include "../BaseObject.h"
#include "../exceptions/InvalidArgumentException.h"
#include "../adressing/IpAddress.h"
#include "../adressing/MacAddress.h"
#include "../exceptions/ParseException.h"

using namespace std;





//    Bytes        Offset
//    char op;                          // 1              0
//    char htype;                       // 1              1
//    char hlen;                        // 1              2
//    char hops;                        // 1              3
//    char xid[4];                      // 4              4
//    char secs[2];                     // 2              8
//    char flags[2];                    // 2              10
//    char ciaddr[4];                   // 4              12
//    char yiaddr[4];                   // 4              16
//    char siaddr[4];                   // 4              20
//    char giaddr[4];                   // 4              24
//    char chaddr[16];                  // 16             28
//    char sname[64];                   // 64             44
//    char file[128];                   // 128            108
//    char options[OPT_SIZE];           // undef          236



static const int _op = 0;
static const int _htype = 1;
static const int _hlen = 2;
static const int _hops = 3;
static const int _xid = 4;
static const int _secs = 8;
static const int _flags = 10;
static const int _ciaddr = 12;
static const int _yiaddr = 16;
static const int _siaddr = 20;
static const int _giaddr = 24;
static const int _chaddr = 28;
static const int _sname = 44;
static const int _file = 108;
static const int _options = 236;

static const int _size_xid = 4;
static const int _size_secs = 2;
static const int _size_flags = 2;
static const int _size_iaddr = 4;
static const int _size_chaddr = 16;
static const int _size_sname = 64;
static const int _size_file = 128;
static const int _size_options = 64;

#define MSG_SIZE_WITH_OPTIONS 240 + 64

static const int _size_message_type = 1;
static const int _size_lease_time = 4;
static const int _size_subnet_mask = 4;
static const int _size_server_identifier = 4;
static const int _size_end = 0;

enum optionType {
    messageTypeID = 53,
    leaseTimeID = 51,
    subnetMaskID = 1,
    serverIdentifierID = 54,
};


class DhcpMessage : public BaseObject {
    const string _name = "DHCP message";


    //////////////////////////actual content of msg/////////////////////////////////////
    unsigned char op;
    unsigned char htype;
    unsigned char hlen;
    unsigned char hops;
    unsigned int xid;
    uint16_t secs;
    uint16_t flags;
    addressing::IpAddress ciaddr;
    addressing::IpAddress yiaddr;
    addressing::IpAddress siaddr;
    addressing::IpAddress giaddr;
    addressing::MacAddress chaddr;
    unsigned char sname[_size_sname];
    unsigned char file[_size_file];

    //options
    unsigned char messageType;
    int leaseTime;
    addressing::IpAddress subnetMask;
    addressing::IpAddress serverIdentifier;
    const unsigned char end = 255;

    ///////////////////////////////////////////////////////////////////////////////////

public:

    ////////METHODS/////////



    DhcpMessage(vector<unsigned char> &msg);

    DhcpMessage &operator=(DhcpMessage other);

    vector<unsigned char> createMessageVector();

    virtual string toString();

    virtual string getLoggableName() {
        return this->_name;
    }


    const addressing::MacAddress &getChaddr() const {
        return chaddr;
    }

    void setChaddr(const addressing::MacAddress &chaddr) {
        DhcpMessage::chaddr = chaddr;
    }


    const addressing::IpAddress &getCiaddr() const {
        return ciaddr;
    }

    void setCiaddr(const addressing::IpAddress &ciaddr) {
        DhcpMessage::ciaddr = ciaddr;
    }

    const addressing::IpAddress &getYiaddr() const {
        return yiaddr;
    }

    void setYiaddr(const addressing::IpAddress &yiaddr) {
        DhcpMessage::yiaddr = yiaddr;
    }

    const addressing::IpAddress &getSiaddr() const {
        return siaddr;
    }

    void setSiaddr(const addressing::IpAddress &siaddr) {
        DhcpMessage::siaddr = siaddr;
    }

    const addressing::IpAddress &getGiaddr() const {
        return giaddr;
    }

    void setGiaddr(const addressing::IpAddress &giaddr) {
        DhcpMessage::giaddr = giaddr;
    }

    const addressing::IpAddress &getSubnetMask() const {
        return subnetMask;
    }

    void setSubnetMask(const addressing::IpAddress &subnetMask) {
        DhcpMessage::subnetMask = subnetMask;
    }

    uint16_t getSecs() {
        return secs;
    }

    void setSecs(uint16_t _secs) {
        this->secs = _secs;
    }

    uint16_t getFlags() {
        return flags;
    }

    void setFlags(uint16_t _flags) {
        this->flags = _flags;
    }

    unsigned char getOP() {
        return op;
    }

    void setOp(unsigned char op) {
        this->op = op;
    }

    unsigned char getHtype() {
        return htype;
    }

    void setHType(unsigned char htype) {
        this->htype = htype;
    }

    unsigned char getHlen() {
        return hlen;
    }

    void setHLen(unsigned char hlen) {
        this->hlen = hlen;
    }

    unsigned char getHOps() {
        return hops;
    }

    void setHOps(unsigned char hops) {
        this->hops = hops;
    }

    unsigned int getXid() {
        return xid;
    }

    void setXid(unsigned int xid) {
        this->xid = xid;
    }

    unsigned char *getSname() {
        return sname;
    }

    void setSname(unsigned char *from) {
        memcpy(this->sname, from, _size_sname);
    }

    unsigned char *getFile() {
        return file;
    }

    void setFile(unsigned char *from) {
        memcpy(this->file, from, _size_file);
    }

    int getLeaseTime() const {
        return leaseTime;
    }

    void setLeaseTime(int leaseTime) {
        DhcpMessage::leaseTime = leaseTime;
    }

    unsigned char getMeesageType() const {
        return messageType;
    }

    void setMeesageType(unsigned char meesageType) {
        DhcpMessage::messageType = meesageType;
    }

    unsigned char getEnd() const {
        return end;
    }

    const addressing::IpAddress &getServerIdentifier() const {
        return serverIdentifier;
    }

    void setServerIdentifier(const addressing::IpAddress &serverIdentifier) {
        DhcpMessage::serverIdentifier = serverIdentifier;
    }

};


#endif //ISA_PROJ_DHCPMESSAGE_H
