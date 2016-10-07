cmake_minimum_required(VERSION 3.6)
project(isa_proj)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp adressing/IpAddress.cpp adressing/IpAddress.h adressing/MacAddress.cpp adressing/MacAddress.h adressing/Timestamp.cpp adressing/Timestamp.h adressing/Reservation.cpp adressing/Reservation.h adressing/AddressPool.cpp adressing/AddressPool.h adressing/AddressHandler.cpp adressing/AddressHandler.h BaseObject.h request/AbstractRequest.cpp request/AbstractRequest.h request/Discover.cpp request/Discover.h request/Request.cpp request/Request.h request/Release.cpp request/Release.h threads/MainThread.cpp threads/MainThread.h threads/ResponseThread.cpp threads/ResponseThread.h threads/CancellableThread.cpp threads/CancellableThread.h sockets/Socket.cpp sockets/Socket.h sockets/MainSocket.cpp sockets/MainSocket.h ProtocolParser.cpp ProtocolParser.h tests/cppUnit.cpp tests/cppUnit.h tests/IpAddrTest.cpp exceptions/ParseException.cpp exceptions/ParseException.h exceptions/BaseException.cpp exceptions/BaseException.h tests/MacAddrTest.cpp tests/testStarter.cpp tests/iph.h tests/mach.h)

set(TEST_FILES tests/IpAddrTest.cpp tests/cppUnit.cpp tests/cppUnit.h adressing/IpAddress.h adressing/IpAddress.cpp exceptions/BaseException.cpp exceptions/BaseException.h exceptions/ParseException.cpp exceptions/ParseException.h adressing/MacAddress.cpp adressing/MacAddress.h tests/MacAddrTest.cpp tests/testStarter.cpp tests/iph.h tests/mach.h)
add_executable(isa_proj ${SOURCE_FILES})
add_executable(tests ${TEST_FILES})
