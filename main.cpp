#include <iostream>
#include <vector>
#include <map>
#include <list>
#include "adressing/IpAddress.h"
#include "sockets/Socket.h"
#include "exceptions/InvalidArgumentException.h"
#include "adressing/AddressHandler.h"
#include "exceptions/ParseException.h"
#include <string.h>
#include <fstream>
#include <iostream>


using namespace addressing;

IpAddress parseNetworkInfo(char* net, int & prefix){
    char* lomitko = strchr(net,'/');
    if(net == NULL)
        throw InvalidArgumentException("Net is not specified correctly, no '/' character'");
    unsigned long ip_addr_len = lomitko - net;
    prefix = stoi(lomitko + 1);
    // is the prefix sane?
    if(prefix <= 0 || prefix > 30){
        string msg = "Invalid prefix: ";
        msg += prefix;
        throw InvalidArgumentException(msg);
    }

    vector<unsigned char> tmp;
    tmp.resize(ip_addr_len);
    memcpy(tmp.data(),net,ip_addr_len);
    IpAddress ipAddress(tmp);
    return ipAddress;
}

void parseReservedAddress(list<IpAddress> &reserved,char* string1){
    static const int MAX_ADDR_SIZE = 3 + 1 + 3 + 1 + 3 + 1 + 3;
    char* begin=string1,*end=NULL;
    unsigned long size;
    char buffer[MAX_ADDR_SIZE+1];
    memset(buffer,'\0',MAX_ADDR_SIZE+1);

    // iterate over the string, remember the position of first character, find next ',' and try to parse anything between

    while((end = strchr(begin,',')) != NULL){
        size = end - begin;
        memcpy(buffer,begin,size);
        IpAddress address(buffer);
        reserved.push_back(address);


        memset(buffer,'\0',size);
        begin = end + 1;
    }

    // now the last address
    IpAddress addr (begin);
    reserved.push_back(addr);
}


void parseDirectMapping(map<MacAddress,IpAddress>& direct_mapping,char* file){
    ifstream infile;
    infile.open(file);
    if(!infile){
        stringstream ss;
        ss << "File " << file << " not found";
        throw InvalidArgumentException(ss.str());
    }
    string mac,ip;
    while(infile >> mac >> ip){
        MacAddress macAddress(mac);
        IpAddress ipAddress(ip);
        direct_mapping.emplace(macAddress,ipAddress);
    }
    infile.close();
}

void parseArguments(int argc, char** argv,IpAddress * networkAddress,int & prefix, list<IpAddress>& reserved, map<MacAddress,IpAddress>& direct_mapping){
    if(argc < 3)
        throw InvalidArgumentException("No enough arguments");
    if(strcmp("-p",argv[1]))
        throw InvalidArgumentException("First param must be '-p'");

    *networkAddress = parseNetworkInfo(argv[2],prefix);
    int index = 3;
    if(argc > 3 && argc != 5 && argc != 7)
        throw InvalidArgumentException("Incorrect amount of arguments");
    while(index < argc){
        if(!strcmp("-e",argv[index])){
            parseReservedAddress(reserved,argv[index+1]);
            index++;
        } else if(!strcmp("-s",argv[index])){
            parseDirectMapping(direct_mapping,argv[index + 1]);
            index++;
        } else {
            stringstream ss;
            ss << "Argument " << argv[index] << "not identified";
            throw InvalidArgumentException(ss.str());
        }
        index++;
    }
}

int main(int argc, char ** argv) {
    IpAddress networkAddress("0.0.0.0");
    int prefix;
    list<IpAddress> reserved;
    map<MacAddress,IpAddress> direct_mapping;

    try{
        parseArguments(argc,argv,&networkAddress,prefix,reserved,direct_mapping);
    }catch (InvalidArgumentException & e){
        std::cerr << e.toString() << std::endl;
    } catch(ParseException & e){
        std::cerr << e.toString() << std::endl;
    }
    AddressHandler handler(networkAddress,prefix,reserved,direct_mapping);
    std::cout << handler.toString() << std::endl;

//    IpAddress address(127,0,0,1);
//    Socket socket1(address);
////    std::vector<char> ret = socket1.getMessage();
////    std::cout << ret.data() << std::endl;
//
//    std::string msg = "Hello, world";
//    socket1.sendMessage(msg,address);
    return 0;
}