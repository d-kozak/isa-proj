//
// Created by david on 6.10.16.
//

#include "cppUnit.h"
#include "../adressing/IpAddress.h"
#include "iph.h"

using namespace addressing;

TEST_CASE(ip_compare,

    IpAddress addr1(192,168,0,0);
    IpAddress addr2("192.168.0.0");
    MY_ASSERT((addr1 == addr2),"IpAddress operator '==' does not work");
);

TEST_CASE(ip_compare2,

    IpAddress addr1(192,168,0,0);
    IpAddress addr2("192.168.1.1");
    MY_ASSERT((addr1 != addr2),"IpAddress operator '!=' does not work");
);

TEST_CASE(ipPrintName,

    IpAddress addr1(192,168,0,0);
    MY_ASSERT(addr1.getLoggableName() == "IpAddress","getNamefailed comparison failed");
);

TEST_CASE(ipToString,

    IpAddress addr1(192,168,0,0);
    MY_ASSERT(addr1.toString() == "IpAddress -> 192.168.0.0","toString comparison failed");
);

TEST_CASE(ipnext,
    IpAddress addr(192,168,0,0);
            cout << "start" << endl;
            cout << addr.toString() << endl;
            using namespace std;
            for (int i = 0; i < 10; ++i) {
                addr = addr.next_addr();
                cout << addr.toString() << endl;
            }
            cout << "end" << endl;

);

TestSuite getIpTestSuite(){
    Test test1("==",ip_compare);
    Test test2("!=",ip_compare2);
    Test test3("printName",ipPrintName);
    Test test4("toString",ipToString);
    Test test5("next",ipnext);


    TestSuite suite("Ip Address suite");
    suite.add(test1);
    suite.add(test2);
    suite.add(test3);
    suite.add(test4);
    suite.add(test5);

    return suite;
}

