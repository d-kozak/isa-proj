//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_CANCELLABLETHREAD_H
#define ISA_PROJ_CANCELLABLETHREAD_H

#include <iostream>
#include <thread>
#include "../BaseObject.h"

class CancellableThread : public BaseObject{
    std::thread _thread;
public:
    void start();
    void interrupt();

    virtual void run() = 0;
};


#endif //ISA_PROJ_CANCELLABLETHREAD_H
