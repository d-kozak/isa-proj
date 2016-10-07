//
// Created by david on 7.10.16.
//

#include "iph.h"
#include "mach.h"
#include "cppUnit.h"

int main(int argc, char **argv) {
    TestExecutor exec;
    TestSuite ipSuite = getIpTestSuite();
    TestSuite macSuite = getMacTestSuite();
    exec.add(ipSuite);
    exec.add(macSuite);

    exec.run();
}