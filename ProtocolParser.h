//
// Created by david on 6.10.16.
//

#ifndef ISA_PROJ_PROTOCOLPARSER_H
#define ISA_PROJ_PROTOCOLPARSER_H


#include "request/AbstractRequest.h"

using namespace std;

class ProtocolParser {
    public:
    AbstractRequest * parseRequest(string);
};


#endif //ISA_PROJ_PROTOCOLPARSER_H
