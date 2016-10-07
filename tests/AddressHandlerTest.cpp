//
// Created by david on 7.10.16.
//

#include "AddressHandlerTest.h"
#include <unistd.h>
#include "../adressing/AddressHandler.h"
#include "../exceptions/InvalidArgumentException.h"

using namespace addressing;

static map<MacAddress, IpAddress> direct_mapping;

TEST_CASE(address_handler_basic,
          try {
              IpAddress first(1, 1, 1, 1);
              int prefix = 30;
              list <IpAddress> reserved;
              AddressHandler handler(first, prefix, reserved, direct_mapping);

              MacAddress mac(5, 5, 5, 5, 5, 5);
              IpAddress result = handler.getAddressFor(mac);
              handler.releaseAddress(mac);
              result = handler.getAddressFor(mac);
              cout << "&&&" << result.toString() << "&&&" << endl;
          } catch(InvalidArgumentException & e){
            cerr << e.what() << endl;
              FAIL;
          }
);

TestSuite getAddressHandlerTestSuite() {
    Test s1("basic",address_handler_basic);

    TestSuite suite("AddressHandler");
    suite.add(s1);
    return suite;
}
