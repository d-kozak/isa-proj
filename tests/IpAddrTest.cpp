//
// Created by david on 6.10.16.
//

#include "cppUnit.h"
#include "../adressing/IpAddress.h"

using namespace addressing;

TEST_CASE(tests_compare,

    IpAddress addr1(192,168,0,0);
    IpAddress addr2("192.168.0.0");
    MY_ASSERT((addr1 == addr2),"IpAddress operator '==' does not work");
);

TEST_CASE(tests_compare2,

    IpAddress addr1(192,168,0,0);
    IpAddress addr2("192.168.1.1");
    MY_ASSERT((addr1 != addr2),"IpAddress operator '!=' does not work");
);

TEST_CASE(testPrintName,

    IpAddress addr1(192,168,0,0);
    MY_ASSERT(addr1.getLoggableName() == "IpAddress","getNamefailed comparison failed");
);

TEST_CASE(testToString,

    IpAddress addr1(192,168,0,0);
    MY_ASSERT(addr1.toString() == "IpAddress -> 192.168.0.0","toString comparison failed");
);

int main(){
    Test test1("==",tests_compare);
    Test test2("!=",tests_compare2);
    Test test3("printName",testPrintName);
    Test test4("toString",testToString);


    TestSuite suite("Ip Address suite");
    suite.add(test1);
    suite.add(test2);
    suite.add(test3);
    suite.add(test4);

    suite.run();
}

