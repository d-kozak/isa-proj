//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_CANCELLABLETHREAD_H
#define ISA_PROJ_CANCELLABLETHREAD_H

#include <iostream>
#include <thread>
#include "../BaseObject.h"

class CancellableThread : public BaseObject{
    const string _name = "CancellableThread";
    std::thread _thread;
    volatile bool _isInterrupted;
public:
    CancellableThread();
    void start();
    void interrupt();

    virtual void performTask() = 0;


    void run();

    virtual string toString();
    virtual string getLoggableName();

};


#endif //ISA_PROJ_CANCELLABLETHREAD_H
