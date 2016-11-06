//
// Created by david on 7.10.16.
//

#include "reservationTest.h"
#include "cppUnit.h"
#include "../../adressing/IpAddress.h"
#include "../../adressing/Timestamp.h"
#include "../../adressing/Reservation.h"

using namespace addressing;

TEST_CASE(ReservationtoStringTest,
          IpAddress address(255, 255, 255, 255);
                  Timestamp stamp;
                  Reservation r(address, stamp);
                  MY_ASSERT(r.toString() == "Reservation -> {(IpAddress -> 255.255.255.255)(TimeStamp -> 0)}","toStringfailed");
);

TestSuite getReservationTestsuite() {
    Test t1("to string",ReservationtoStringTest);

    TestSuite suite("Reservation suite");
    suite.add(t1);
    return suite;
}
