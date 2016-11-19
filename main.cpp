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
static volatile Socket* sock = NULL;
static volatile int isInterrupted = 0;
static volatile int retVal = 0;

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

void printHelp() {
    static const string txt = "Usage: ./dserver -p <netAddr>/<prefix> [-e <exluded1>,<exluded12>,...] [-d <file>]\n"
            "-e allow excluded addresses\n"
            "-d allow direct mapping\n";
    cout << txt;
}

void intHandler(int dummy) {
    cout << "Interrupting" << endl;
    mainLock.lock();
    isInterrupted = 1;
    sock->closeSocket(); // closing socket at this point will probably cause exception in the main thread,
    // that is why we first set isInterupted flag, so that the main thread knows the reason for the exception
    mainLock.unlock();
}

void serverLoop(AddressHandler &handler) {
    signal(SIGINT, intHandler);

    Socket socket1(handler.getServerAddress());
    sock = &socket1; // store pointer to the socket in global volatile variable, so that the interrupt handler can close the socket

    ProtocolParser parser;
    cout << "Starting" << endl;
    while (!isInterrupted) {
        try {
            vector<unsigned char> msg = socket1.getMessage();
            std::lock_guard<std::mutex> guard(mainLock); //acquire the lock for the duration of request handling
            DhcpMessage dhcpMessage(msg);
            AbstractRequest *req = parser.parseRequest(dhcpMessage); //dynamic allocation and dealocation is handled by protocol parser
            req->performTask(handler);
        } catch (SocketException &e) {
            if(isInterrupted){
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
    cout << "Finishing" << endl;
}

int main(int argc, char **argv) {
    IpAddress networkAddress("0.0.0.0");
    int prefix;
    list <IpAddress> reserved;
    map<MacAddress, IpAddress> direct_mapping;

    try {
        parseArguments(argc, argv, &networkAddress, prefix, reserved, direct_mapping);
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
    }
    catch (SocketException &e) {
        std::cerr << e.toString() << std::endl;
        printHelp();
        return ERR_PARAMS;
    }
//    AddressHandler handler(networkAddress, prefix, reserved, direct_mapping);
//    std::cout << handler.toString() << std::endl;

//    IpAddress address(127,0,0,1);
//    Socket socket1(address);
////    std::vector<char> ret = socket1.getMessage();
////    std::cout << ret.data() << std::endl;
//
//    std::string msg = "Hello, world";
//    socket1.sendMessage(msg,address);
    return retVal;
}