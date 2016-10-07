//
// Created by david on 7.10.16.
//

#include "TimestampTest.h"
#include "../adressing/Timestamp.h"
#include <unistd.h>

using namespace addressing;

TEST_CASE(tt_construct,
    Timestamp t;
);

TEST_CASE(tt_compare,
          Timestamp t1;
          Timestamp t2;
          MY_ASSERT(t1 != t2,"compare should have failed")
);


TEST_CASE(tt_is_lease_expired,
          Timestamp t1;
                  MY_ASSERT(!t1.isLeaseExpired(),"lease should not have expired yet")
);

TEST_CASE(tt_to_string,
          Timestamp t1;
                  sleep(1);
                  MY_ASSERT(t1.toString() == "TimeStamp -> 1","1 second should have passed until the object was created")
);

TestSuite getTimestampTestsuite(){
    Test t1("constuctTest",tt_construct);
    Test t2("compareTest",tt_compare);
    Test t3("leaseExpiredTest",tt_is_lease_expired);
    Test t4("leaseExpiredTest",tt_to_string);

    TestSuite suite("TimeStamp");
    suite.add(t1);
    suite.add(t2);
    suite.add(t3);
    suite.add(t4);
    return suite;
}