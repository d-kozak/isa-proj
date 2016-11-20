//
// Created by david on 7.10.16.
//

#include "iph.h"
#include "mach.h"
#include "cppUnit.h"
#include "TimestampTest.h"
#include "AddressPairTest.h"
#include "AddressPoolTest.h"
#include "AddressCollectorTest.h"
#include "AddressHandlerTest.h"
#include "../../sockets/Socket.h"

/**
 * Dependencies simulating real values... tests do not use them, the variables are just needed during build time
 */
volatile Socket *sock;
volatile int isInterrupted =  false;

int main(int argc, char **argv) {
    TestExecutor exec;
    TestSuite ipSuite = getIpTestSuite();
    TestSuite macSuite = getMacTestSuite();
    TestSuite ttSuite = getTimestampTestsuite();
    TestSuite s1 = getAddressPairTestsuite();
    TestSuite s2 = getAddressPoolTestsuite();
    TestSuite s3 = getAddressCollectorTestSuite();
    TestSuite s4 = getAddressHandlerTestSuite();
    exec.add(ipSuite);
    exec.add(macSuite);
    exec.add(ttSuite);
    exec.add(s1);
    exec.add(s2);
    exec.add(s3);
    exec.add(s4);
    exec.run();
}