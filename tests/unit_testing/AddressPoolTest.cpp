//
// Created by david on 7.10.16.
//

#include "AddressPoolTest.h"

#include "../../adressing/IpAddress.h"
#include "../../adressing/AddressPool.h"

using namespace addressing;

bool pool_complex_tests() {
    IpAddress first(192, 168, 0, 0);
    int prefix = 24;
    list <IpAddress> reserved;
    map<MacAddress, IpAddress> direct_mapping;
    AddressPool pool(first, prefix, reserved, direct_mapping);
    MacAddress mac1("aa:aa:aa:aa:aa:aa");
    MacAddress mac2("bb:aa:aa:aa:aa:aa");
    MacAddress mac3("cc:aa:aa:aa:aa:aa");
    MacAddress mac4("dd:aa:aa:aa:aa:aa");
    MacAddress mac5("ee:aa:aa:aa:aa:aa");


    pool.getAddress(mac1);
    IpAddress a3 = pool.getAddress(mac2);
    pool.getAddress(mac3);
    MY_ASSERT(pool.getAddress(mac4).toString() == "IpAddress -> 192.168.0.5", "should be x.x.x.5");

    pool.releaseAddress(a3);
    MY_ASSERT(pool.getAddress(mac5).toString() == "IpAddress -> 192.168.0.6", "should be x.x.x.6");

    return true; // !!!!
}

TestSuite getAddressPoolTestsuite() {
    Test t1("construcor", pool_complex_tests);

    TestSuite suite("AddressPool");
    suite.add(t1);

    return suite;
}
