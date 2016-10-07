//
// Created by david on 7.10.16.
//

#include "iph.h"
#include "mach.h"
#include "cppUnit.h"
#include "TimestampTest.h"
#include "reservationTest.h"

int main(int argc, char **argv) {
    TestExecutor exec;
    TestSuite ipSuite = getIpTestSuite();
    TestSuite macSuite = getMacTestSuite();
    TestSuite ttSuite = getTimestampTestsuite();
    TestSuite reserSuite = getReservationTestsuite();
    exec.add(ipSuite);
    exec.add(macSuite);
    exec.add(ttSuite);
    exec.add(reserSuite);

    exec.run();
}