//
// Created by david on 7.10.16.
//

#include "AddressPairTest.h"
#include "../../adressing/AddressPool.h"

using namespace addressing;

TEST_CASE(AddressPairToString,
          IpAddress addr(192,168,0,1);
        AddressPair pair(addr);
                  MY_ASSERT(pair.toString() == "AddressPair -> (IpAddress -> 192.168.0.1, free)","toStringfailed");
                  pair.setIsFree(false);
                  MY_ASSERT(pair.toString() == "AddressPair -> (IpAddress -> 192.168.0.1, reserved)","toStringfailed2");
);

TestSuite getAddressPairTestsuite(){
    Test t1("toString",AddressPairToString);

    TestSuite suite("AddressPair");
    suite.add(t1);
    return suite;
}
