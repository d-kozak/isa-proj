//
// Created by david on 6.10.16.
//

#include "MainThread.h"
#include "ResponseThread.h"

MainThread::MainThread(addressing::AddressHandler &handler, addressing::IpAddress &first) : _handler(handler),
                                                                                            _socket(first), _parser() {}

void MainThread::printStatistics() {}


void MainThread::performTask() {
    vector<char> msg = this->_socket.getMessage();
    DhcpMessage dhcp_msg(msg);
    AbstractRequest *req = this->_parser.parseRequest(dhcp_msg);
    ResponseThread thread(_handler,req);
    thread.start();
}
