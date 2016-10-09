//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_MAINTHREAD_H
#define ISA_PROJ_MAINTHREAD_H


#include "../BaseObject.h"
#include "CancellableThread.h"
#include "../adressing/AddressHandler.h"
#include "../sockets/Socket.h"
#include "../ProtocolParser.h"

class MainThread : public CancellableThread{
    addressing::AddressHandler &_handler;
    Socket _socket;
    ProtocolParser _parser;

public:
    MainThread(addressing::AddressHandler & hadler,addressing::IpAddress & first);
    void printStatistics();
    void performTask();
};


#endif //ISA_PROJ_MAINTHREAD_H
