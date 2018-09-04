# Simple DHCP server implementation in C/C++

## ISA PROJECT 2016
* Author: David Kozak
* Contact: xkozak15@stud.fit.vutbr.cz

## Usage:
make -> to build the project 

To run it:
 ./dserver -p <net-address>/prefix [-e excluded1,excluded2,...,excludedN] [-s file]
 -p specify net address and the prefix
 -e addresses excluded from the pool
 -s static mapping of MAC to IP

## Project structure
* ./addressing package
  -classes modeling IP and MAC addresses, AddressPool of the server,...
* ./exceptions package
  -classes for both application specific and universal exceptions
  such as InvalidArgumentException,ParseException,SocketException,...
* ./request package
  -classes modeling DHCP messages
* ./sockets package
  -basic socket communication using BSD sockets
* ./tests package
  -unit tests
* ./threads package
  -currently unused package containing implementation of universal thread and cancellable "infinite looper"  thread
* ./BaseObject.h
  -declaration of universal superclass containing pure virtual methods every class in this project has to implement
* ./constants.h
  -constants used throughout the project
* ./main.cpp
  -file containing main method and argument parsing
* ./Makefile
  -make file which builds this project
  
For more details see documentation doc.pdf(warning - It is written in Czech)
