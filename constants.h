//
// Created by david on 18.10.16.
//

#ifndef ISA_PROJ_CONSTANTS_H
#define ISA_PROJ_CONSTANTS_H

#include "adressing/IpAddress.h"

#define LEASE_TIME 6
//1 * 60 * 60;

enum retVals {
    EOK,
    ERR_PARAMS,
    ERR_SOCKET
};

const addressing::IpAddress NULL_IP(0,0,0,0);

#endif //ISA_PROJ_CONSTANTS_H
