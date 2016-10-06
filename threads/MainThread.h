//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_MAINTHREAD_H
#define ISA_PROJ_MAINTHREAD_H


#include "../BaseObject.h"
#include "CancellableThread.h"

class MainThread : public CancellableThread{

public:
    void parseArguments();
    void printStatistics();
    virtual void run();
};


#endif //ISA_PROJ_MAINTHREAD_H
