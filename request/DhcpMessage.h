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

#define OPT_SIZE 10
#define CURRENT_MSG_SIZE 248

using namespace std;

class DhcpMessage : public BaseObject {
    const string _name = "DHCP message";
public:
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
    char buffer[CURRENT_MSG_SIZE + 1];

    const int op = 0;
    const int htype = 1;
    const int hlen = 2;
    const int hops = 3;
    const int xid = 4;
    const int secs = 8;
    const int flags = 10;
    const int ciaddr = 12;
    const int yiaddr = 16;
    const int siaddr = 20;
    const int giaddr = 24;
    const int chaddr = 28;
    const int sname = 44;
    const int file = 110;
    const int options = 238;
    const int message_type = options + 0;

    const int size_xid = 4;
    const int size_secs = 2;
    const int size_flags = 2;
    const int size_iaddr = 4;
    const int size_maddr = 16;
    const int size_sname = 64;
    const int size_file = 128;
    const int size_options = OPT_SIZE;

    ////////METHODS/////////

    DhcpMessage(){
        memset(buffer,'\0',CURRENT_MSG_SIZE + 1);
    }

    DhcpMessage(vector<char>& msg){
        if(msg.size() != CURRENT_MSG_SIZE){
            string x = "Invalid msg size";
            x += to_string(msg.size());
            throw InvalidArgumentException(x);
        }

        memcpy(buffer,msg.data(),CURRENT_MSG_SIZE);
        buffer[CURRENT_MSG_SIZE] = '\0';
    }


    void check_indexing(int index, int size){
        if(index + size >= CURRENT_MSG_SIZE){
            stringstream ss;
            ss << "index and size are bigger than the underlying buffer" << endl;
            ss << index << "  + " << size << " = " << index + size << "is bigger than " << CURRENT_MSG_SIZE << endl;
            throw InvalidArgumentException(ss.str());
        }
    }

    // returns given item in a vector containing its string representation(ends with one additional \0)
    vector<char> getItemAsVector(int index, int size){
        check_indexing(index, size);

        // prepare the vector
        std::vector<char> res;
        res.resize(size+1);
        res.data()[size] = '\0';

        memcpy(res.data(),buffer + index,size);
        return res;
    }

    char* getItem(int offset){
        return buffer + offset;
    }

    void setPartOfBuffer(int index, int size,void* source){
        check_indexing(index,size);
        memcpy(buffer+index,source,size);
    }

    vector<char> createMessageVector(){
        buffer[CURRENT_MSG_SIZE] = '\0';
        vector<char> v;
        v.resize(CURRENT_MSG_SIZE + 1);
        memcpy(v.data(),buffer,CURRENT_MSG_SIZE);
        v.data()[CURRENT_MSG_SIZE] = '\0';
        return v;
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

    DhcpMessage &operator=(DhcpMessage other) {
        memcpy(this->buffer,other.buffer,CURRENT_MSG_SIZE);
        return *this;
    }

};


#endif //ISA_PROJ_DHCPMESSAGE_H
