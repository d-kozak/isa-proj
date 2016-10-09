#include <iostream>
#include <vector>
#include "adressing/IpAddress.h"
#include "sockets/Socket.h"

using namespace addressing;

int main() {
    IpAddress address(127,0,0,1);
    Socket socket1(address);
//    std::vector<char> ret = socket1.getMessage();
//    std::cout << ret.data() << std::endl;

    std::string msg = "Hello, world";
    socket1.sendMessage(msg,address);
    return 0;
}