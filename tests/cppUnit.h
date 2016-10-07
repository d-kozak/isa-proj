//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_CPPUNIT_H
#define ISA_PROJ_CPPUNIT_H

#include <iostream>
#include <list>

#define MY_ASSERT(expr, msg) do {\
                            if(!(expr)) { std::cerr << "\t\t" <<msg << std::endl; return false;}\
                        } while(0)

#define TEST_CASE(name,body) bool name(){body;return true;}

class Test{
    const std::string _name;
    bool (*_f)(void);

public:
    Test(std::string name,bool (*f)(void));
    virtual bool run();
};

class TestSuite {
    const std::string _name;
    std::list<Test> _tests;

public:
    TestSuite(std::string name);
    TestSuite(std::string name,std::list<Test> tests);

    void add(Test & test);
    virtual bool run();
};

class TestExecutor {
    std::list<TestSuite> _tests;
public:
    TestExecutor(std::list<TestSuite> list);
    TestExecutor();

    void add(TestSuite & suite);
    void run();
};

#endif //ISA_PROJ_CPPUNIT_H
