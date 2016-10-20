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

#define OPT_SIZE 10
#define CURRENT_MSG_SIZE 248

using namespace std;

class DhcpMessage : public BaseObject {
    const string _name = "DHCP message";

                                      // Bytes        Offset
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
//    char file[128];                   // 128            110
//    char options[OPT_SIZE];           // undef          238
//                                                        238 + OPT_SIZE (for now 248)


    const int _op = 0;
    const int _htype = 1;
    const int _hlen = 2;
    const int _hops = 3;
    const int _xid = 4;
    const int _secs = 8;
    const int _flags = 10;
    const int _ciaddr = 12;
    const int _yiaddr = 16;
    const int _siaddr = 20;
    const int _giaddr = 24;
    const int _chaddr = 28;
    const int _sname = 44;
    const int _file = 110;
    const int _options = 238;
    const int _message_type = _options + 0;
    const int _lease_time = _options + _size_message_type;
    const int _subnestMask = _options + _size_message_type + _size_lease_time;
    const int _end = _options + _size_message_type + _size_lease_time + _size_subnet_mask;

    const int _size_xid = 4;
    const int _size_secs = 2;
    const int _size_flags = 2;
    const int _size_iaddr = 4;
    const int _size_chaddr = 16;
    const int _size_sname = 64;
    const int _size_file = 128;

    const int _size_message_type = 1;
    const int _size_lease_time = 4;
    const int _size_subnet_mask = 4;
    const int _size_end = 0;
    const int _size_options = OPT_SIZE;

    //////////////////////////actual content of msg/////////////////////////////////////
    unsigned char op;
    unsigned char htype;
    unsigned char hlen;
    unsigned char hops;
    unsigned int xid;
    unsigned char secs[_size_secs];
    unsigned char flags[_size_flags];
    addressing::IpAddress ciaddr;
    addressing::IpAddress yiaddr;
    addressing::IpAddress siaddr;
    addressing::IpAddress giaddr;
    addressing::MacAddress chaddr;
    unsigned char sname[_size_sname];
    unsigned char file[_size_file];
    unsigned char meesageType;

    int leaseTime;
    addressing::IpAddress subnetMask;
    unsigned char end;
    //////////////////////////actual content of msg/////////////////////////////////////


    void appendToVec(vector<unsigned char>& vec, unsigned char* source,int size){
        for (int i = 0; i < size; ++i) {
            vec.push_back(source[i]);
        }
    }

    void appendToVec(vector<unsigned char>& destination,addressing::IpAddress& addr){
        vector<unsigned char> from = addr.asVector();
        destination.insert(destination.end(),from.begin(),from.end());
    }


public:

    ////////METHODS/////////



    DhcpMessage(vector<unsigned char>& msg){
        initFromMsg(msg);
    }

    DhcpMessage initFromMsg(vector<unsigned char>& msg){

    }



    DhcpMessage &operator=(DhcpMessage other) {
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
        this->setEnd(other.getEnd());
        return *this;
    }

    vector<unsigned char> createMessageVector(){
        vector<unsigned char> ret;
        ret.push_back(op);
        ret.push_back(htype);
        ret.push_back(hlen);
        ret.push_back(hops);
        appendToVec(ret,(unsigned char*) &xid,ADDRESS_SIZE);
        appendToVec(ret,secs,_size_secs);
        appendToVec(ret,flags,_size_flags);
        appendToVec(ret,ciaddr);
        appendToVec(ret,yiaddr);
        appendToVec(ret,siaddr);
        appendToVec(ret,giaddr);
        appendToVec(ret,sname,_size_sname);
        appendToVec(ret,file,_size_file);
        ret.push_back(meesageType);
        appendToVec(ret,(unsigned char*) &leaseTime,_size_lease_time);
        appendToVec(ret,subnetMask);
        ret.push_back(end);
        return ret;
    }



    virtual string toString(){
        stringstream ss;
        ss << this->_name + " -> " << "{" << endl;
        ss << this->createMessageVector().data() << endl;
        ss << "}";
        return ss.str();
    }

    virtual string getLoggableName(){
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

    unsigned char* getSecs(){
        return secs;
    }

    void setSecs(unsigned char* secs){
        memcpy(this->secs,secs,_size_secs);
    }

    unsigned char* getFlags(){
        return flags;
    }

    void setFlags(unsigned char* flags){
        memcpy(this->flags,flags,_size_flags);
    }

    unsigned char getOP(){
        return op;
    }

    void setOp(unsigned char op){
        this->op = op;
    }

    unsigned char getHtype(){
        return htype;
    }

    void setHType(unsigned char htype){
        this->htype= htype;
    }

    unsigned char getHlen(){
        return hlen;
    }

    void setHLen(unsigned char hlen){
        this->hlen= hlen;
    }

    unsigned char getHOps(){
        return hops;
    }

    void setHOps(unsigned char hops){
        this->hops = hops;
    }

    unsigned int getXid(){
        return xid;
    }

    void setXid(unsigned int xid){
        this->xid = xid;
    }

    unsigned char *getSname() const {
        return sname;
    }

    void setSname(unsigned char* from){
        memcpy(this->sname,from,_size_sname);
    }

    unsigned char *getFile() const {
        return file;
    }

    void setFile(unsigned char* from){
        memcpy(this->file,from,_size_file);
    }

    int getLeaseTime() const {
        return leaseTime;
    }

    void setLeaseTime(int leaseTime) {
        DhcpMessage::leaseTime = leaseTime;
    }

    unsigned char getMeesageType() const {
        return meesageType;
    }

    void setMeesageType(unsigned char meesageType) {
        DhcpMessage::meesageType = meesageType;
    }

    unsigned char getEnd() const {
        return end;
    }

    void setEnd(unsigned char end) {
        DhcpMessage::end = end;
    }

};


#endif //ISA_PROJ_DHCPMESSAGE_H
