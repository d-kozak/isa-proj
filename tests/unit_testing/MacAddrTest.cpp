//
// Created by david on 7.10.16.
//

#include "cppUnit.h"
#include "../../adressing/MacAddress.h"
#include "mach.h"

using namespace addressing;

TEST_CASE(mac_compare,

          MacAddress addr1(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
          MacAddress addr2(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
                  MY_ASSERT((addr1 == addr2), "IpAddress operator '==' does not work");
);

TEST_CASE(mac_compare2,

          MacAddress addr1(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
                  MacAddress addr2(192, 168, 0, 0, 0, 1);
                  MY_ASSERT((addr1 != addr2), "IpAddress operator '!=' does not work");
);

TEST_CASE(macPrintName,

          MacAddress addr1(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
                  MY_ASSERT(addr1.getLoggableName() == "MacAddress", "getNamefailed comparison failed");
);

TEST_CASE(macToString,

          MacAddress addr1(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
                  std:: cout << addr1.toString() << std::endl;
                  MY_ASSERT(addr1.toString() == "ff:ff:ff:ff:ff:ff", "toString comparison failed");
);

TestSuite getMacTestSuite(){
    Test test1("==", mac_compare);
    Test test2("!=", mac_compare2);
    Test test3("printName", macPrintName);
    Test test4("toString", macToString);


    TestSuite suite("Mac Address suite");
    suite.add(test1);
    suite.add(test2);
    suite.add(test3);
    suite.add(test4);

    return suite;
}

