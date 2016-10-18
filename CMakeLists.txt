cmake_minimum_required(VERSION 3.6)
project(isa_proj)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES
        main.cpp
#        adressing/IpAddress.cpp adressing/IpAddress.h
#        adressing/MacAddress.cpp adressing/MacAddress.h
#        adressing/Timestamp.cpp adressing/Timestamp.h
#        adressing/Reservation.cpp adressing/Reservation.h
#        adressing/AddressPool.cpp adressing/AddressPool.h
#        adressing/AddressHandler.cpp adressing/AddressHandler.h
#        BaseObject.h
#        request/AbstractRequest.cpp request/AbstractRequest.h
#        request/Discover.cpp request/Discover.h
#        request/Request.cpp request/Request.h
#        request/Release.cpp request/Release.h
#        threads/MainThread.cpp threads/MainThread.h t
#        hreads/ResponseThread.cpp threads/ResponseThread.h
#        threads/CancellableThread.cpp threads/CancellableThread.h
#        sockets/Socket.cpp sockets/Socket.h
#        sockets/MainSocket.cpp sockets/MainSocket.h
#        ProtocolParser.cpp ProtocolParser.h
#        exceptions/ParseException.cpp exceptions/ParseException.h
#        exceptions/BaseException.cpp exceptions/BaseException.h
        )

set(TEST_FILES tests/cppUnit.cpp tests/cppUnit.h

        BaseObject.h

        adressing/IpAddress.cpp adressing/IpAddress.h
        adressing/MacAddress.cpp adressing/MacAddress.h
        adressing/Reservation.cpp adressing/Reservation.h
        adressing/Timestamp.cpp adressing/Timestamp.h
        adressing/AddressPool.cpp adressing/AddressPool.h
        adressing/AddressHandler.cpp adressing/AddressHandler.h


        sockets/Socket.cpp sockets/Socket.h

        request/AbstractRequest.cpp request/AbstractRequest.h
        request/Discover.cpp request/Discover.h
        request/Release.cpp request/Release.h
        request/Request.cpp request/Request.h
        request/DhcpMessage.cpp request/DhcpMessage.h

        threads/CancellableThread.cpp threads/CancellableThread.h
        threads/ResponseThread.cpp threads/ResponseThread.h
        threads/MainThread.cpp threads/MainThread.h

        exceptions/BaseException.cpp exceptions/BaseException.h
        exceptions/ParseException.cpp exceptions/ParseException.h
        exceptions/OutOfAddressException.cpp exceptions/OutOfAddressException.h
        exceptions/InvalidArgumentException.cpp exceptions/InvalidArgumentException.h
        exceptions/SocketException.cpp exceptions/SocketException.h

        tests/testStarter.cpp
        tests/MacAddrTest.cpp tests/mach.h
        tests/IpAddrTest.cpp tests/iph.h
        tests/TimestampTest.cpp tests/TimestampTest.h
        tests/reservationTest.cpp tests/reservationTest.h
        tests/AddressPairTest.cpp tests/AddressPairTest.h
        tests/AddressPoolTest.cpp tests/AddressPoolTest.h
        tests/AddressCollectorTest.cpp tests/AddressCollectorTest.h
        tests/AddressHandlerTest.cpp tests/AddressHandlerTest.h constants.h)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/david/projects/isa-proj/output")

set(PROGRAM_FILES

        main.cpp

        adressing/IpAddress.cpp adressing/IpAddress.h
        adressing/MacAddress.cpp adressing/MacAddress.h
        adressing/Reservation.cpp adressing/Reservation.h
        adressing/Timestamp.cpp adressing/Timestamp.h
        adressing/AddressPool.cpp adressing/AddressPool.h
        adressing/AddressHandler.cpp adressing/AddressHandler.h


        sockets/Socket.cpp sockets/Socket.h

        request/AbstractRequest.cpp request/AbstractRequest.h
        request/Discover.cpp request/Discover.h
        request/Release.cpp request/Release.h
        request/Request.cpp request/Request.h

        threads/CancellableThread.cpp threads/CancellableThread.h
        threads/ResponseThread.cpp threads/ResponseThread.h
        threads/MainThread.cpp threads/MainThread.h

        exceptions/BaseException.cpp exceptions/BaseException.h
        exceptions/ParseException.cpp exceptions/ParseException.h
        exceptions/OutOfAddressException.cpp exceptions/OutOfAddressException.h
        exceptions/InvalidArgumentException.cpp exceptions/InvalidArgumentException.h
        exceptions/SocketException.cpp exceptions/SocketException.h

        request/DhcpMessage.cpp request/DhcpMessage.h request/Offer.cpp request/Offer.h constants.h)


add_executable(isa_proj ${PROGRAM_FILES})
add_executable(tests ${TEST_FILES})
