#include <iostream>
#include <vector>
#include "adressing/IpAddress.h"
#include "sockets/Socket.h"
#include "exceptions/InvalidArgumentException.h"
#include <string.h>

using namespace addressing;

int main(int argc, char ** argv) {
    if(argc < 3)
        throw InvalidArgumentException("No enough arguments");
    if(strcmp("-p",argv[1]))
        throw InvalidArgumentException("First param must be '-p'");
    char* net = argv[2];
    char* lomitko = strchr(net,'/');
    if(net == NULL)
        throw InvalidArgumentException("Net is not specified correctly, no '/' character'");
    unsigned long lomitko_pos = lomitko - net;
    int prefix = stoi(lomitko + 1);
    vector<char> addr;
    addr.resize(lomitko - net + 1);
    memcpy(addr.data(),net,lomitko - net);
    addr.data()[lomitko - net] = '\0';
    IpAddress ipAddress(addr);


//    IpAddress address(127,0,0,1);
//    Socket socket1(address);
////    std::vector<char> ret = socket1.getMessage();
////    std::cout << ret.data() << std::endl;
//
//    std::string msg = "Hello, world";
//    socket1.sendMessage(msg,address);
    return 0;
}