//
// Created by david on 20.10.16.
//

#ifndef ISA_PROJ_THREADWRAPPER_H
#define ISA_PROJ_THREADWRAPPER_H


#include <iostream>
#include <thread>
#include "../BaseObject.h"

using namespace std;

class ThreadWrapper: public BaseObject{
    const string _name = "CancellableThread";
    std::thread _thread;

    virtual void start() = 0;
public:
    ThreadWrapper();
    void start();
    void join();
    virtual void run() = 0;

    virtual string toString();
    virtual string getLoggableName();

};



#endif //ISA_PROJ_THREADWRAPPER_H
