//
// Created by david on 20.10.16.
//

#include "ThreadWrapper.h"


ThreadWrapper::ThreadWrapper() : _thread() {}

void ThreadWrapper::start() {
    this->_thread = thread([this] { this->run(); });
}

string ThreadWrapper::toString() const {
    return this->_name;
}

string ThreadWrapper::getLoggableName() const  {
    return this->_name;
}

void ThreadWrapper::join() {
    this->_thread.join();
}
