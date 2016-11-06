//
// Created by david on 7.10.16.
//

#include "AddressCollectorTest.h"
#include <unistd.h>
#include "../../adressing/AddressHandler.h"

using namespace addressing;

static map<MacAddress, IpAddress> direct_mapping;

TEST_CASE(collector_basic,
          IpAddress first(1,1,1,1);
                  int prefix = 30;
                  list<IpAddress> reserved;
    AddressHandler handler(first,prefix, reserved,direct_mapping);
          handler.start();
          sleep(2);
          handler.interrupt();
);


TestSuite getAddressCollectorTestSuite(){

    Test t1("basic functionality",collector_basic);

    TestSuite s("AddressCollector");
    s.add(t1);

    return s;
}
