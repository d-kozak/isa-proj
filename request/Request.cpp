//
// Created by david on 6.10.16.
//

#include "Request.h"

void Request::performTask(){

}

void Request::after(){

}

string Request::toString(){
    return this->_name;
}

string Request::getLoggableName(){
    return this->_name;
}
