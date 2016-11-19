//
// see header for details
//

#include "MainThread.h"
#include "ResponseThread.h"

MainThread::MainThread(addressing::AddressHandler &handler, addressing::IpAddress &first) : _handler(handler),
                                                                                            _socket(first), _parser() {}

void MainThread::printStatistics() {}


void MainThread::performTask() {
    vector<unsigned char> msg = this->_socket.getMessage();
    ResponseThread thread(_handler,_parser,msg);
    thread.start();
}
