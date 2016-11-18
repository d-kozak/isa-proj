//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_CANCELLABLETHREAD_H
#define ISA_PROJ_CANCELLABLETHREAD_H

#include <iostream>
#include <thread>
#include "../BaseObject.h"
#include "ThreadWrapper.h"

class CancellableThread : public ThreadWrapper {
    const string _name = "CancellableThread";
    volatile bool _isInterrupted;
public:
    CancellableThread();
    void interrupt();

    virtual void performTask() = 0;
    virtual void run();

    virtual string toString() const ;
    virtual string getLoggableName() const ;

};


#endif //ISA_PROJ_CANCELLABLETHREAD_H
