#Makefile for ISA projects - DHCP server
#I use cmake to compile my project in clion... this makefile was mostly generated by a shell script I had written, that is why it looks quite ugly

#compiler
CC=g++

#optimization
OPT=-O2

#flags
#CPPFLAGS= -std=c++11 -Wall -Wextra -pedantic -pthread 
CPPFLAGS= -std=c++11 -pthread

#name of the executable
EXEC_NAME=dserver
TEST_EXEC=unittest

FILES_FULL_PATH=./sockets/Socket.o ./request/Release.o ./request/Discover.o ./request/Request.o ./request/Offer.o ./request/DhcpMessage.o ./request/Ack.o ./request/AbstractRequest.o ./request/Nack.o ./adressing/IpAddress.o ./adressing/Timestamp.o ./adressing/AddressHandler.o ./adressing/AddressPool.o ./adressing/MacAddress.o ./exceptions/SocketException.o ./exceptions/BaseException.o ./exceptions/OutOfAddressException.o ./exceptions/ParseException.o ./exceptions/InvalidArgumentException.o
FILES=Socket.o Release.o Discover.o Request.o Offer.o DhcpMessage.o Ack.o AbstractRequest.o Nack.o IpAddress.o Timestamp.o AddressHandler.o AddressPool.o MacAddress.o SocketException.o BaseException.o OutOfAddressException.o ParseException.o InvalidArgumentException.o

ALL_FILES=./sockets/Socket.cpp ./sockets/Socket.h ./tests/unit_testing/AddressPoolTest.h ./tests/unit_testing/AddressPairTest.cpp ./tests/unit_testing/AddressHandlerTest.h ./tests/unit_testing/AddressPoolTest.cpp ./tests/unit_testing/AddressPairTest.h ./tests/unit_testing/testStarter.cpp ./tests/unit_testing/IpAddrTest.cpp ./tests/unit_testing/MacAddrTest.cpp ./tests/unit_testing/AddressCollectorTest.cpp ./tests/unit_testing/mach.h ./tests/unit_testing/AddressCollectorTest.h ./tests/unit_testing/TimestampTest.h ./tests/unit_testing/cppUnit.h ./tests/unit_testing/TimestampTest.cpp ./tests/unit_testing/AddressHandlerTest.cpp ./tests/unit_testing/iph.h ./tests/unit_testing/cppUnit.cpp ./constants.h ./main.cpp ./request/Release.cpp ./request/Discover.cpp ./request/Discover.h ./request/Request.h ./request/Request.cpp ./request/Offer.cpp ./request/Nack.h ./request/DhcpMessage.h ./request/DhcpMessage.cpp ./request/Release.h ./request/Ack.cpp ./request/AbstractRequest.cpp ./request/Ack.h ./request/Offer.h ./request/AbstractRequest.h ./request/Nack.cpp ./BaseObject.h ./threads/ThreadWrapper.h ./threads/CancellableThread.cpp ./threads/ThreadWrapper.cpp ./threads/MainThread.cpp ./threads/ResponseThread.h ./threads/MainThread.h ./threads/CancellableThread.h ./threads/ResponseThread.cpp ./adressing/IpAddress.h ./adressing/IpAddress.cpp ./adressing/Timestamp.cpp ./adressing/AddressHandler.cpp ./adressing/AddressPool.cpp ./adressing/AddressPool.h ./adressing/MacAddress.h ./adressing/MacAddress.cpp ./adressing/Timestamp.h ./adressing/AddressHandler.h ./exceptions/OutOfAddressException.h ./exceptions/SocketException.cpp ./exceptions/BaseException.cpp ./exceptions/OutOfAddressException.cpp ./exceptions/SocketException.h ./exceptions/ParseException.cpp ./exceptions/InvalidArgumentException.h ./exceptions/ParseException.h ./exceptions/BaseException.h ./exceptions/InvalidArgumentException.cpp

TEST_FULL_PATH=./tests/unit_testing/AddressPairTest.o ./tests/unit_testing/AddressPoolTest.o ./tests/unit_testing/IpAddrTest.o ./tests/unit_testing/MacAddrTest.o ./tests/unit_testing/AddressCollectorTest.o ./tests/unit_testing/TimestampTest.o ./tests/unit_testing/AddressHandlerTest.o ./tests/unit_testing/cppUnit.o
TEST_FILES=AddressPairTest.o AddressPoolTest.o IpAddrTest.o MacAddrTest.o AddressCollectorTest.o TimestampTest.o AddressHandlerTest.o cppUnit.o

THREADING_FULL_PATH=./threads/CancellableThread.o ./threads/ThreadWrapper.o ./threads/MainThread.o ./threads/ResponseThread.o
THREADING_FILES=CancellableThread.o ThreadWrapper.o MainThread.o ResponseThread.o


.PHONY: build
.PHONY: clean
.PHONY: distrib

build: ${EXEC_NAME}

${EXEC_NAME}: ${FILES_FULL_PATH} ./main.o
	${CC} ${CPPFLAGS} ${FILES} main.o -o ${EXEC_NAME} ${OPT} 


${TEST_EXEC}: ${FILES_FULL_PATH} ./tests/unit_testing/testStarter.o ${TEST_FULL_PATH}
	${CC} ${CPPFLAGS} ${FILES} ${TEST_FILES} testStarter.o -o ${TEST_EXEC} ${OPT}

./sockets/Socket.o : ./sockets/Socket.cpp
	${CC} ${CPPFLAGS} ./sockets/Socket.cpp ${OPT}  -c
./tests/unit_testing/AddressPairTest.o : ./tests/unit_testing/AddressPairTest.cpp
	${CC} ${CPPFLAGS} ./tests/unit_testing/AddressPairTest.cpp ${OPT}  -c
./tests/unit_testing/AddressPoolTest.o : ./tests/unit_testing/AddressPoolTest.cpp
	${CC} ${CPPFLAGS} ./tests/unit_testing/AddressPoolTest.cpp ${OPT}  -c
./tests/unit_testing/testStarter.o : ./tests/unit_testing/testStarter.cpp
	${CC} ${CPPFLAGS} ./tests/unit_testing/testStarter.cpp ${OPT}  -c
./tests/unit_testing/IpAddrTest.o : ./tests/unit_testing/IpAddrTest.cpp
	${CC} ${CPPFLAGS} ./tests/unit_testing/IpAddrTest.cpp ${OPT}  -c
./tests/unit_testing/MacAddrTest.o : ./tests/unit_testing/MacAddrTest.cpp
	${CC} ${CPPFLAGS} ./tests/unit_testing/MacAddrTest.cpp ${OPT}  -c
./tests/unit_testing/AddressCollectorTest.o : ./tests/unit_testing/AddressCollectorTest.cpp
	${CC} ${CPPFLAGS} ./tests/unit_testing/AddressCollectorTest.cpp ${OPT}  -c
./tests/unit_testing/TimestampTest.o : ./tests/unit_testing/TimestampTest.cpp
	${CC} ${CPPFLAGS} ./tests/unit_testing/TimestampTest.cpp ${OPT}  -c
./tests/unit_testing/AddressHandlerTest.o : ./tests/unit_testing/AddressHandlerTest.cpp
	${CC} ${CPPFLAGS} ./tests/unit_testing/AddressHandlerTest.cpp ${OPT}  -c
./tests/unit_testing/cppUnit.o : ./tests/unit_testing/cppUnit.cpp
	${CC} ${CPPFLAGS} ./tests/unit_testing/cppUnit.cpp ${OPT}  -c
./main.o : ./main.cpp
	${CC} ${CPPFLAGS} ./main.cpp ${OPT}  -c
./request/Release.o : ./request/Release.cpp
	${CC} ${CPPFLAGS} ./request/Release.cpp ${OPT}  -c
./request/Discover.o : ./request/Discover.cpp
	${CC} ${CPPFLAGS} ./request/Discover.cpp ${OPT}  -c
./request/Request.o : ./request/Request.cpp
	${CC} ${CPPFLAGS} ./request/Request.cpp ${OPT}  -c
./request/Offer.o : ./request/Offer.cpp
	${CC} ${CPPFLAGS} ./request/Offer.cpp ${OPT}  -c
./request/DhcpMessage.o : ./request/DhcpMessage.cpp
	${CC} ${CPPFLAGS} ./request/DhcpMessage.cpp ${OPT}  -c
./request/Ack.o : ./request/Ack.cpp
	${CC} ${CPPFLAGS} ./request/Ack.cpp ${OPT}  -c
./request/AbstractRequest.o : ./request/AbstractRequest.cpp
	${CC} ${CPPFLAGS} ./request/AbstractRequest.cpp ${OPT}  -c
./request/Nack.o : ./request/Nack.cpp
	${CC} ${CPPFLAGS} ./request/Nack.cpp ${OPT}  -c
./threads/CancellableThread.o : ./threads/CancellableThread.cpp
	${CC} ${CPPFLAGS} ./threads/CancellableThread.cpp ${OPT}  -c
./threads/ThreadWrapper.o : ./threads/ThreadWrapper.cpp
	${CC} ${CPPFLAGS} ./threads/ThreadWrapper.cpp ${OPT}  -c
./threads/MainThread.o : ./threads/MainThread.cpp
	${CC} ${CPPFLAGS} ./threads/MainThread.cpp ${OPT}  -c
./threads/ResponseThread.o : ./threads/ResponseThread.cpp
	${CC} ${CPPFLAGS} ./threads/ResponseThread.cpp ${OPT}  -c
./adressing/IpAddress.o : ./adressing/IpAddress.cpp
	${CC} ${CPPFLAGS} ./adressing/IpAddress.cpp ${OPT}  -c
./adressing/Timestamp.o : ./adressing/Timestamp.cpp
	${CC} ${CPPFLAGS} ./adressing/Timestamp.cpp ${OPT}  -c
./adressing/AddressHandler.o : ./adressing/AddressHandler.cpp
	${CC} ${CPPFLAGS} ./adressing/AddressHandler.cpp ${OPT}  -c
./adressing/AddressPool.o : ./adressing/AddressPool.cpp
	${CC} ${CPPFLAGS} ./adressing/AddressPool.cpp ${OPT}  -c
./adressing/MacAddress.o : ./adressing/MacAddress.cpp
	${CC} ${CPPFLAGS} ./adressing/MacAddress.cpp ${OPT}  -c
./exceptions/SocketException.o : ./exceptions/SocketException.cpp
	${CC} ${CPPFLAGS} ./exceptions/SocketException.cpp ${OPT}  -c
./exceptions/BaseException.o : ./exceptions/BaseException.cpp
	${CC} ${CPPFLAGS} ./exceptions/BaseException.cpp ${OPT}  -c
./exceptions/OutOfAddressException.o : ./exceptions/OutOfAddressException.cpp
	${CC} ${CPPFLAGS} ./exceptions/OutOfAddressException.cpp ${OPT}  -c
./exceptions/ParseException.o : ./exceptions/ParseException.cpp
	${CC} ${CPPFLAGS} ./exceptions/ParseException.cpp ${OPT}  -c
./exceptions/InvalidArgumentException.o : ./exceptions/InvalidArgumentException.cpp
	${CC} ${CPPFLAGS} ./exceptions/InvalidArgumentException.cpp ${OPT}  -c

distrib:
	tar -cvf xkozak15.tar ${ALL_FILES} Makefile README manual.pdf ./tests/msgs/*

clean:
	rm -f ${FILES} ${TEST_EXEC} ${TEST_FILES} ${EXEC_NAME} ${THREADING_FILES} main.o testStarter.o
	rm -f xkozak15.tar
