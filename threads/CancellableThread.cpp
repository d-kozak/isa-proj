//
// Created by david on 6.10.16.
//

#include <sstream>
#include "CancellableThread.h"

CancellableThread::CancellableThread():_thread(),_isInterrupted(false){}

void CancellableThread::start(){
    this->_thread = thread([this] { this->run();});
}

void CancellableThread::interrupt(){
    this->_isInterrupted = true;
}

void CancellableThread::run(){
    while(!_isInterrupted){
        this->performTask();
    }
}

string CancellableThread::toString(){
    stringstream ss;
    ss << this->_name << " -> {" << endl;
    ss << "\t";
    if(this->_isInterrupted)
        ss << "interrupted";
    else
        ss << "running";
    ss << endl;
    ss << "}";
    return ss.str();
}

string CancellableThread::getLoggableName(){
    return this->_name;
}
