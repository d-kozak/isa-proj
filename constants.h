//
// Header file containing some of the global constants which are not class-specific
//

#ifndef ISA_PROJ_CONSTANTS_H
#define ISA_PROJ_CONSTANTS_H

#include "adressing/IpAddress.h"

/**
 * lengtgh of one lease
 */
#define LEASE_TIME 1 * 60
// one minute

/**
 * global debugging flag
 */
#define DEBUG 0

/**
 * return values of the program
 */
enum RET_VALS {
    EOK,
    ERR_PARAMS,
    ERR_SOCKET
};

/**
 * values for the OP field in DHCP message
 */
enum BOOTP_TYPE{
    BOOT_REQUEST = 1,
    BOOT_REPLY = 2
};

/**
 * DHPC message types
 */
enum REQUEST_TYPE {
    DISCOVER=1, OFFER=2, REQUEST=3, ACK=5, NACK=6, RELEASE=7
};

/*
 * specival constant representing empty IpAddress
 */
const addressing::IpAddress NULL_IP(0,0,0,0);

#endif //ISA_PROJ_CONSTANTS_H
