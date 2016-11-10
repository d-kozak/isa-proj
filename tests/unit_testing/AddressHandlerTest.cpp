//
// Created by david on 7.10.16.
//

#include "AddressHandlerTest.h"
#include <unistd.h>
#include "../../adressing/AddressHandler.h"
#include "../../exceptions/InvalidArgumentException.h"

using namespace addressing;

static map<MacAddress, IpAddress> direct_mapping;

TEST_CASE(address_handler_basic,
          try {
              IpAddress first(1, 1, 1, 1);
              int prefix = 28;
              list <IpAddress> reserved;
              AddressHandler handler(first, prefix, reserved, direct_mapping);

              handler.start();

              MacAddress mac1(5, 5, 5, 5, 5, 5);
              MacAddress mac2(1, 1, 1, 1, 1, 1);
              MacAddress mac3(2, 2,2, 2, 2, 2);
              IpAddress result1 = handler.getAddressFor(mac1);
              handler.confirmBindingFor(result1,mac1);
              IpAddress result2 = handler.getAddressFor(mac2);
              handler.confirmBindingFor(result2,mac2);
              IpAddress result3 = handler.getAddressFor(mac3);
              handler.confirmBindingFor(result3,mac3);
              handler.releaseAddress(mac1);
              result3 = handler.getAddressFor(mac1);


              handler.interrupt();

          } catch (InvalidArgumentException &e) {
              cerr << e.what() << endl;
              FAIL;
          }
);

TEST_CASE(address_handler_advanced,
          try {
              IpAddress first(1, 1, 1, 1);
              int prefix = 28;
              list <IpAddress> reserved;
              AddressHandler handler(first, prefix, reserved, direct_mapping);

              MacAddress mac(5, 5, 5, 5, 5, 5);
              MacAddress mac2(1, 1, 1, 1, 1, 1);
              // start the gc
              handler.start();

              IpAddress result = handler.getAddressFor(mac);
              handler.confirmBindingFor(result,mac);
              handler.printCurrentState();
              // now wait for the address to expire :)
              sleep(2);
              handler.getAddressFor(mac2);
              sleep(2);
              handler.printCurrentState();
              sleep(2);
              handler.printCurrentState();
              handler.interrupt();
              cout << "AFTER INTERRUPT" << endl;
              sleep(1);
              handler.printCurrentState();
          } catch (InvalidArgumentException &e) {
              cerr << e.what() << endl;
              FAIL;
          }
);

TestSuite getAddressHandlerTestSuite() {
    Test s1("basic", address_handler_basic);
    Test s2("advanced", address_handler_advanced);

    TestSuite suite("AddressHandler");
    suite.add(s1);
    suite.add(s2);
    return suite;
}
