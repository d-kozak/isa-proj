//
// Created by david on 7.10.16.
//

#include "AddressPoolTest.h"

#include "../adressing/IpAddress.h"
#include "../adressing/AddressPool.h"

using namespace addressing;

TEST_CASE(pool_constructor,
          IpAddress first(192, 168, 0, 0);
                  int prefix = 24;
                  list <IpAddress> reserved;
          AddressPool pool(first,prefix,reserved);



);

TestSuite getAddressPoolTestsuite() {
    Test t1("construcor",pool_constructor);

    TestSuite suite("AddressPool");
    suite.add(t1);

    return suite;
}
