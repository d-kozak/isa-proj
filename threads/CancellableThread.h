#ifndef ISA_PROJ_CANCELLABLETHREAD_H
#define ISA_PROJ_CANCELLABLETHREAD_H

#include <iostream>
#include <thread>
#include "../BaseObject.h"
#include "ThreadWrapper.h"

/**
 * Class represents any thread that is supposed to execute specific task in a loop and can be interrupted
 * If you wan to use it, inherit from this class and implement the perform task method
 */
class CancellableThread : public ThreadWrapper {
    const string _name = "CancellableThread";
    /**
     * flag for the interruption
     */
    volatile bool _isInterrupted;
public:
    CancellableThread();

    /**
     * interrupts the thread
     */
    void interrupt();

    /**
     * pure virtual method in which subclasses specify their  repeated 'task'
     */
    virtual void performTask() = 0;

    /**
     * executes perfromTask in a loop until the flag is set
     */
    virtual void run();

    virtual string toString() const ;
    virtual string getLoggableName() const ;

};


#endif //ISA_PROJ_CANCELLABLETHREAD_H
