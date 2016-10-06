//
// Created by david on 6.10.16.
//

#include "cppUnit.h"

bool tst(){
    MY_ASSERT(true,"ERROR IN TEST FRAMEWORK");
//    MY_ASSERT(false,"ASSERT FAILED");
    return true;
}

int main(){
    Test test("Basic test",tst);
    TestSuite suite("Basic suite");
    suite.add(test);
    TestExecutor exec;
    exec.add(suite);

    exec.run();

}

