#include <iostream>
#include <vector>
#include <map>
#include <list>
#include "adressing/IpAddress.h"
#include "sockets/Socket.h"
#include "exceptions/InvalidArgumentException.h"
#include "adressing/AddressHandler.h"
#include "exceptions/ParseException.h"
#include "constants.h"
#include "request/DhcpMessage.h"
#include "request/AbstractRequest.h"
#include "exceptions/SocketException.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <signal.h>
#include <mutex>
/**
 * Main file of the project
 * contains argument parsing and main method
 */

using namespace addressing;
/**
 * Mutex used for cooperation between signal handler and
 * main loop of the server.
 * The server has to acquire this lock right after he received a message and leaves it after sending the response.
 * Signal handler has to acuire it before starting the cleaning process which ends up by deleting all dynamically  allocated objects
 * and setting the interrupt flag to true.
 * This means that the after receiving SIGINT, the server will handle its last request, unlocks lock
 * and then the interrupt handler will start cleaning.
 */
static std::mutex mainLock;

/**
 * reference to the socket so that it can be closed from the signal handler
 */
volatile Socket *sock = NULL;

/**
 * Interrupt flag for maintrhead <=> signal handler communication
 */
volatile int isInterrupted = 0;

/**
 * return value of the program
 */
static volatile int retVal = EOK;


/**
 * checks if the specified reserved addresses and static assignments are actualy from the specified pool
 * @param netAddr address of the network
 * @param prefix prefix
 * @param reserved reserved ip address
 * @param direct_mapping statically assigned ip addresses
 */
void checkArguments(IpAddress & netAddrObj,int prefix, list <IpAddress> &reserved,
                    map<MacAddress, IpAddress> &direct_mapping){
    uint32_t  netMask = ntohl(IpAddress::getNetMaskFor(prefix).getAddrForSocket());
    uint32_t netAddressInt = netAddrObj.getAddrForSocket();

    // check reserved addresses
    for(auto & item : reserved){
        uint32_t address = item.getAddrForSocket();
        uint32_t subnetOfThisAddress = address & netMask;
        if(subnetOfThisAddress != netAddressInt){
            stringstream ss;
            ss << "Address " << item.toString() << " is not in the subnet " << netAddrObj.toString() << "/" << prefix << endl;
            throw InvalidArgumentException(ss.str());
        }
    }

    //check static assignments
    for(auto & item : direct_mapping){
        uint32_t address = item.second.getAddrForSocket();
        if(address & netMask != netAddressInt){
            stringstream ss;
            ss << "Address " << item.second.toString() << " is not in the subnet " << netAddrObj.toString() << "/" << prefix << endl;
            throw InvalidArgumentException(ss.str());
        }
    }
}

/**
 * parses the ip address of the network and prefix
 * @return the ip address of the network
 * @throws InvalidArgumentException if the arguments are invalid
 */
IpAddress parseNetworkInfo(char *net, int &prefix) {
    try {
        char *lomitko = strchr(net, '/');
        if (lomitko == NULL)
            throw InvalidArgumentException("Net is not specified correctly, no '/' character'");
        unsigned long ip_addr_len = lomitko - net;
        prefix = stoi(lomitko + 1);
        // is the prefix sane?
        if (prefix <= 0 || prefix > 30) {
            string msg = "Invalid prefix: ";
            msg += prefix;
            throw InvalidArgumentException(msg);
        }

        vector<unsigned char> tmp;
        tmp.resize(ip_addr_len);
        memcpy(tmp.data(), net, ip_addr_len);
        IpAddress ipAddress(tmp);
        return ipAddress;

    } catch (std::invalid_argument &e) {}
    catch (std::out_of_range &e) {}
    throw InvalidArgumentException("Wrong net/prefix format");
}

/**
 * function parses reserved ip addresses from char* string1
 * @param reserved list into which the ip addresses are saved
 * @param string1 string contating the addresses
 * @throws ParseException if the format is invalid
 */
void parseReservedAddress(list <IpAddress> &reserved, char *string1) {
    static const int MAX_ADDR_SIZE = 3 + 1 + 3 + 1 + 3 + 1 + 3;
    char *begin = string1, *end = NULL;
    unsigned long size;
    char buffer[MAX_ADDR_SIZE + 1];
    memset(buffer, '\0', MAX_ADDR_SIZE + 1);

    // iterate over the string, remember the position of first character, find next ',' and try to parse anything between

    while ((end = strchr(begin, ',')) != NULL) {
        size = end - begin;
        memcpy(buffer, begin, size);
        IpAddress address(buffer);
        reserved.push_back(address);


        memset(buffer, '\0', size);
        begin = end + 1;
    }

    // now the last address
    IpAddress addr(begin);
    reserved.push_back(addr);
}


/**
 * function parses static address assignment from file
 * @param direct_mapping map where the result is saved
 * @param file file concating the static assignments
 * @throws InvalidArgumentException if the file does not exist
 */
void parseDirectMapping(map<MacAddress, IpAddress> &direct_mapping, char *file) {
    ifstream infile;
    infile.open(file);
    if (!infile) {
        stringstream ss;
        ss << "File " << file << " not found";
        throw InvalidArgumentException(ss.str());
    }
    string mac, ip;
    while (infile >> mac >> ip) {
        MacAddress macAddress(mac);
        IpAddress ipAddress(ip);
        direct_mapping.emplace(macAddress, ipAddress);
    }
    infile.close();
}

/**
 * parses program arguments
 * @param argc self explanatory
 * @param argv selft explanatory
 *
 * output params:
 * @param networkAddress address of the network
 * @param prefix prefix of the network
 * @param reserved list of reserved addresses
 * @param direct_mapping map of static assignments
 * @throws InvalidArgumentException if the format of the arguments is invalid
 */
void parseArguments(int argc, char **argv, IpAddress *networkAddress, int &prefix, list <IpAddress> &reserved,
                    map<MacAddress, IpAddress> &direct_mapping) {
    if (argc < 3)
        throw InvalidArgumentException("No enough arguments");
    if (strcmp("-p", argv[1]))
        throw InvalidArgumentException("First param must be '-p'");

    *networkAddress = parseNetworkInfo(argv[2], prefix);
    int index = 3;
    if (argc > 3 && argc != 5 && argc != 7)
        throw InvalidArgumentException("Incorrect amount of arguments");
    while (index < argc) {
        if (!strcmp("-e", argv[index])) {
            parseReservedAddress(reserved, argv[index + 1]);
            index++;
        } else if (!strcmp("-s", argv[index])) {
            parseDirectMapping(direct_mapping, argv[index + 1]);
            index++;
        } else {
            stringstream ss;
            ss << "Argument " << argv[index] << "not identified";
            throw InvalidArgumentException(ss.str());
        }
        index++;
    }
}


/**
 * prints help
 */
void printHelp() {
    static const string txt = "Usage: ./dserver -p <netAddr>/<prefix> [-e <exluded1>,<exluded12>,...] [-d <file>]\n"
            "-e allow excluded addresses\n"
            "-d allow direct mapping\n";
    cout << txt;
}

/**
 * Hadler of the SIGINT signal
 * interrupts the mainloop by setting interrupt flag and closing the socket
 * @param dummy dummy param
 */
void intHandler(int dummy) {
    if (DEBUG)
        cout << "Interrupting" << endl;
    mainLock.lock();
    isInterrupted = 1;
    sock->closeSockets(); // closing socket at this point will probably cause exception in the main thread,
    // that is why we first set isInterupted flag, so that the main thread knows the reason for the exception
    mainLock.unlock();
}


/**
 * main loop of the program
 * listens on a socket, gets a message, parses it and replies, then waits again
 * the loop is brokem from the SIGINT signal handler
 * @param handler address handler
 */
void serverLoop(AddressHandler &handler) {
    signal(SIGINT, intHandler); //register the signal handler

    Socket socket1;
    sock = &socket1; // store pointer to the socket in global volatile variable, so that the interrupt handler can close the socket

    ProtocolParser parser;
    if (DEBUG)
        cout << "Starting" << endl;
    handler.startTheAddressCollector();
    while (!isInterrupted) {
        try {
            vector<unsigned char> msg = socket1.getMessage();
            std::lock_guard<std::mutex> guard(mainLock); //acquire the lock for the duration of request handling
            DhcpMessage dhcpMessage(msg);
            AbstractRequest *req = parser.parseRequest(
                    dhcpMessage); //dynamic allocation and dealocation is handled by protocol parser
            req->performTask(handler);
        } catch (SocketException &e) {
            if (isInterrupted) {
                // if the flag was set already by interrupt handler, we return the retval zero (the exception was raised by handler closing the socket)
                break;
            } else {
                // if this exception was raised because of some "real" socket error, we print err message, set retval and exit
                std::cerr << e.toString() << std::endl;
                retVal = ERR_SOCKET;
                break;
            }
        } catch (BaseException &e) {
            std::cerr << e.toString() << std::endl;
        }
    }
    if (DEBUG)
        cout << "Finishing" << endl;
}

/**
 * main function of the program
 * parses the arguments, creates the address handler with underlying addressPool, then goes into the main serverloop
 * @return one of the RET_VAL enum
 * @see RET_VAL in constants.h
 */
int main(int argc, char **argv) {
    IpAddress networkAddress("0.0.0.0");
    int prefix;
    list <IpAddress> reserved;
    map<MacAddress, IpAddress> direct_mapping;

    try {
        parseArguments(argc, argv, &networkAddress, prefix, reserved, direct_mapping);
        checkArguments(networkAddress,prefix,reserved,direct_mapping);
        AddressHandler handler(networkAddress, prefix, reserved, direct_mapping);
        serverLoop(handler);
    } catch (InvalidArgumentException &e) {
        std::cerr << e.toString() << std::endl;
        printHelp();
        return ERR_PARAMS;
    } catch (ParseException &e) {
        std::cerr << e.toString() << std::endl;
        printHelp();
        return ERR_PARAMS;
    } catch (SocketException &e) {
        std::cerr << e.toString() << std::endl;
        printHelp();
        return ERR_SOCKET;
    }
    return retVal;
}