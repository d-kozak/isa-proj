//
// Created by david on 7.10.16.
//

#include "AddressPoolTest.h"

#include "../adressing/IpAddress.h"
#include "../adressing/AddressPool.h"

using namespace addressing;

TEST_CASE(pool_complex_tests,
          IpAddress first(192, 168, 0, 0);
                  int prefix = 24;
                  list <IpAddress> reserved;
          AddressPool pool(first,prefix,reserved);
//          pool.printCurrentState();
        using namespace std;
          pool.getAddress();
          IpAddress a3 = pool.getAddress();
          pool.getAddress();
          MY_ASSERT(pool.getAddress().toString() == "IpAddress -> 192.168.0.5","should be .x.x.x.5");

            pool.releaseAddress(a3);
          MY_ASSERT(pool.getAddress().toString() == "IpAddress -> 192.168.0.3","should be .x.x.x.3");

);

TestSuite getAddressPoolTestsuite() {
    Test t1("construcor",pool_complex_tests);

    TestSuite suite("AddressPool");
    suite.add(t1);

    return suite;
}
