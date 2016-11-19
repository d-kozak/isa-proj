#ifndef ISA_PROJ_MAINTHREAD_H
#define ISA_PROJ_MAINTHREAD_H


#include "../BaseObject.h"
#include "CancellableThread.h"
#include "../adressing/AddressHandler.h"
#include "../sockets/Socket.h"
#include "../request/AbstractRequest.h"

/**
 * Class implementing the main server loop
 */
class MainThread : public CancellableThread{
    /**
     * handler which connect the thread to the pool
     */
    addressing::AddressHandler &_handler;

    /**
     * socket cunrently used
     */
    Socket _socket;

    /**
     * parser which parses incomming mesages
     */
    ProtocolParser _parser;

public:
    MainThread(addressing::AddressHandler & hadler,addressing::IpAddress & first);
    /**
     * print statistics about current situaction of the thread
     */
    void printStatistics();

    /**
     * implementation of the behaviour of the cancecalle thread, just read message and try to respond
     * @see CancellableThread
     */
    void performTask();
};


#endif //ISA_PROJ_MAINTHREAD_H
