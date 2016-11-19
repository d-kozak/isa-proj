#ifndef ISA_PROJ_THREADWRAPPER_H
#define ISA_PROJ_THREADWRAPPER_H


#include <iostream>
#include <thread>
#include "../BaseObject.h"

using namespace std;

/**
 * Class wraps classic std::thread, enables creating an instance and starting the thread later
 * If you want to use this class, inherit from it and implement the run method which specifies behaviour of the thread
 */
class ThreadWrapper: public BaseObject{
    const string _name = "ThreadWrapper";

    /**
     * underlying thread object
     */
    std::thread _thread;

    /**
     * pure virtual method
     * by implementing it, subclasses specify their behaviour
     */
    virtual void run() = 0;
public:
    ThreadWrapper();

    /**
     * starts the underlying thread
     */
    void start();

    /**
     * joins the thread
     */
    void join();

    virtual string toString() const ;
    virtual string getLoggableName() const ;

};



#endif //ISA_PROJ_THREADWRAPPER_H
