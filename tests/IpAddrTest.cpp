//
// Created by david on 6.10.16.
//

#include "cppUnit.h"
#include "../adressing/IpAddress.h"

using namespace addressing;

bool tests_compare(){
    IpAddress addr1(192,168,0,0);
    IpAddress addr2("192.168.0.0");
    MY_ASSERT((addr1 == addr2),"IpAddress operator '==' does not work");
    return true;
}

bool tests_compare2(){
    IpAddress addr1(192,168,0,0);
    IpAddress addr2("192.168.1.1");
    MY_ASSERT((addr1 != addr2),"IpAddress operator '!=' does not work");
    return true;
}

int main(){
    Test test1("Test ==",tests_compare);
    Test test2("Test !=",tests_compare);


    TestSuite suite("Ip Address suite");
    suite.add(test1);
    suite.add(test2);

    suite.run();
}

