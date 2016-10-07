//
// Created by david on 6.10.16.
//

#include "cppUnit.h"


Test::Test(std::string name, bool (*f)(void)) : _f(f), _name(name) {}

bool Test::run() {
    std::cout << "\tTest " + _name + " started" << std::endl;
    bool res = _f();
    if (!res)
        std::cerr << "\tTest " + _name + " failed" << std::endl;
    std::cout << "\tTest " + _name + " finished" << std::endl;
    return res;
}


TestSuite::TestSuite(std::string name) : _name(name), _tests() {}

TestSuite::TestSuite(std::string name, std::list<Test> tests) : _name(name), _tests(tests) {}

void TestSuite::add(Test &test) {
    _tests.push_back(test);
}


bool TestSuite::run() {
    std::cout << "TestSuite " + _name + " started" << std::endl;
    for (Test &test : _tests) {
        if (!test.run()) {
            std::cerr << "Test suite " + _name + " failed" << std::endl;
            return false;
        }
    }
    std::cout << "TestSuite " + _name + " finished" << std::endl;
    return true;
}


TestExecutor::TestExecutor(std::list<TestSuite> list) : _tests(list) {}

TestExecutor::TestExecutor() : _tests() {}

void TestExecutor::add(TestSuite &suite) {
    _tests.push_back(suite);
}

void TestExecutor::run() {
    std::cout << "-----------TESTS STARTED------------" << std::endl;
    for (TestSuite &suite : _tests) {
        if (!suite.run()) {
            std::cerr << "-----------TESTS FAILED-------------" << std::endl;
            return;
        }
    }
    std::cout << "-------------SUCCESS----------------" << std::endl;
}
