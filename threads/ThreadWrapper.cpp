//
// see header for details
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
