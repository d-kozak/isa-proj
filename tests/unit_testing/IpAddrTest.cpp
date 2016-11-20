//
// Created by david on 6.10.16.
//

#include "cppUnit.h"
#include "../../adressing/IpAddress.h"
#include "iph.h"
#include <bitset>

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
    MY_ASSERT(addr1.toString() == "192.168.0.0","toString comparison failed");
);

TEST_CASE(ipnext,
    IpAddress addr(192,168,0,0);
    IpAddress addr2 = addr.next_addr();
            MY_ASSERT(addr2.toString() == "192.168.0.1","next_addr(void) did not compute correct address");
//            cout << "start" << endl;
//            cout << addr.toString() << endl;
//            using namespace std;
//            for (int i = 0; i < 260; ++i) {
//                addr = addr.next_addr();
//                cout << addr.toString() << endl;
//            }
//            cout << "end" << endl;

);

TEST_CASE(ipnextint,
          IpAddress addr1(192,168,0,0);
          IpAddress addr2 = addr1.next_addr(5);
          MY_ASSERT(addr2.toString() == "192.168.0.5","next_addr(int) did not compute correct address");
);

TEST_CASE(ipnextdist,
    IpAddress addr(254,168,0,0);
            cout << "start" << endl;
            cout << addr.toString() << endl;
            using namespace std;
            for (int i = 1; i < 100000000; i+= 50000) {
                addr = addr.next_addr(i);
                cout << addr.toString() << endl;
            }
            cout << "end" << endl;

);

TEST_CASE(ipToInt,
    IpAddress addr(255,127,63,31);
            bitset<32> correct(0b11111111011111110011111100011111);
          bitset<32> res(addr.getAddrForSocket());
            MY_ASSERT(res == correct,"Comparison failed");
);

TEST_CASE(ipToInt2,
          IpAddress addr(0,0,0,0);
                  bitset<32> correct(0b00000000000000000000000000000000);
                  bitset<32> res(addr.getAddrForSocket());
                  MY_ASSERT(res == correct,"Comparison failed");
);

TEST_CASE(ipToInt3,
          IpAddress addr(255,253,128,7);
                  bitset<32> correct(0b11111111111111011000000000000111);
                  bitset<32> res(addr.getAddrForSocket());
                  cout << correct << endl;
                  cout << res << endl;
                  MY_ASSERT(res == correct,"Comparison failed");
);


TestSuite getIpTestSuite(){
    Test test1("==",ip_compare);
    Test test2("!=",ip_compare2);
    Test test3("printName",ipPrintName);
    Test test4("toString",ipToString);
    Test test5("next",ipnext);
    Test test6("next(int)",ipnextint);
//    Test test7("next(int)",ipnextdist);
    Test test8("toInt",ipToInt);
    Test test9("toInt2",ipToInt2);
    Test test10("toInt3",ipToInt3);



    TestSuite suite("Ip Address suite");
    suite.add(test1);
    suite.add(test2);
    suite.add(test3);
    suite.add(test4);
    suite.add(test5);
    suite.add(test6);
//    suite.add(test7);
    suite.add(test8);
    suite.add(test9);
    suite.add(test10);

    return suite;
}

