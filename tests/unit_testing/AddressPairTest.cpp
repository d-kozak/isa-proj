//
// Created by david on 7.10.16.
//

#include "AddressPairTest.h"
#include "../../adressing/AddressPool.h"

using namespace addressing;

TEST_CASE(AddressPairToString,
          IpAddress addr(192,168,0,1);
        AddressInfo pair(addr);
                  MY_ASSERT(pair.toString() == "AddressInfo -> (IpAddress -> 192.168.0.1, FREE)","toStringfailed");
                  pair.setState(addressing::BINDED);
                  MY_ASSERT(pair.toString() == "AddressInfo -> (IpAddress -> 192.168.0.1, BINDED)","toStringfailed2");
);

TestSuite getAddressPairTestsuite(){
    Test t1("toString",AddressPairToString);

    TestSuite suite("AddressInfo");
    suite.add(t1);
    return suite;
}
