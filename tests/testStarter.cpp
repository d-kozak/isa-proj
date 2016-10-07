//
// Created by david on 7.10.16.
//

#include "iph.h"
#include "mach.h"
#include "cppUnit.h"
#include "TimestampTest.h"
#include "reservationTest.h"
#include "AddressPairTest.h"

int main(int argc, char **argv) {
    TestExecutor exec;
    TestSuite ipSuite = getIpTestSuite();
    TestSuite macSuite = getMacTestSuite();
    TestSuite ttSuite = getTimestampTestsuite();
    TestSuite reserSuite = getReservationTestsuite();
    TestSuite s1 = getAddressPairTestsuite();
    exec.add(ipSuite);
    exec.add(macSuite);
    exec.add(ttSuite);
    exec.add(reserSuite);
    exec.add(s1);

    exec.run();
}