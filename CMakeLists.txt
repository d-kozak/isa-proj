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

set(TEST_FILES tests/unit_testing/cppUnit.cpp tests/unit_testing/cppUnit.h
        constants.h

        BaseObject.h


        adressing/IpAddress.cpp adressing/IpAddress.h
        adressing/MacAddress.cpp adressing/MacAddress.h
        adressing/Timestamp.cpp adressing/Timestamp.h
        adressing/AddressPool.cpp adressing/AddressPool.h
        adressing/AddressHandler.cpp adressing/AddressHandler.h


        sockets/Socket.cpp sockets/Socket.h

        request/AbstractRequest.cpp request/AbstractRequest.h
        request/Discover.cpp request/Discover.h
        request/Release.cpp request/Release.h
        request/Request.cpp request/Request.h
        request/Offer.cpp request/Offer.h
        request/DhcpMessage.cpp request/DhcpMessage.h

        threads/ThreadWrapper.cpp threads/ThreadWrapper.h
        threads/CancellableThread.cpp threads/CancellableThread.h
        threads/ResponseThread.cpp threads/ResponseThread.h
        threads/MainThread.cpp threads/MainThread.h

        exceptions/BaseException.cpp exceptions/BaseException.h
        exceptions/ParseException.cpp exceptions/ParseException.h
        exceptions/OutOfAddressException.cpp exceptions/OutOfAddressException.h
        exceptions/InvalidArgumentException.cpp exceptions/InvalidArgumentException.h
        exceptions/SocketException.cpp exceptions/SocketException.h

        tests/unit_testing/testStarter.cpp
        tests/unit_testing/MacAddrTest.cpp tests/unit_testing/mach.h
        tests/unit_testing/IpAddrTest.cpp tests/unit_testing/iph.h
        tests/unit_testing/TimestampTest.cpp tests/unit_testing/TimestampTest.h
        tests/unit_testing/reservationTest.cpp tests/unit_testing/reservationTest.h
        tests/unit_testing/AddressPairTest.cpp tests/unit_testing/AddressPairTest.h
        tests/unit_testing/AddressPoolTest.cpp tests/unit_testing/AddressPoolTest.h
        tests/unit_testing/AddressCollectorTest.cpp tests/unit_testing/AddressCollectorTest.h
        tests/unit_testing/AddressHandlerTest.cpp tests/unit_testing/AddressHandlerTest.h request/Ack.cpp request/Ack.h request/Nack.cpp request/Nack.h)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/david/projects/isa-proj/output")

set(PROGRAM_FILES

        main.cpp
        constants.h

        adressing/IpAddress.cpp adressing/IpAddress.h
        adressing/MacAddress.cpp adressing/MacAddress.h
        adressing/Timestamp.cpp adressing/Timestamp.h
        adressing/AddressPool.cpp adressing/AddressPool.h
        adressing/AddressHandler.cpp adressing/AddressHandler.h


        sockets/Socket.cpp sockets/Socket.h

        request/AbstractRequest.cpp request/AbstractRequest.h
        request/Discover.cpp request/Discover.h
        request/Release.cpp request/Release.h
        request/Request.cpp request/Request.h
        request/Offer.cpp request/Offer.h

        request/DhcpMessage.cpp request/DhcpMessage.h

        threads/ThreadWrapper.cpp threads/ThreadWrapper.h
        threads/CancellableThread.cpp threads/CancellableThread.h
        threads/ResponseThread.cpp threads/ResponseThread.h
        threads/MainThread.cpp threads/MainThread.h

        exceptions/BaseException.cpp exceptions/BaseException.h
        exceptions/ParseException.cpp exceptions/ParseException.h
        exceptions/OutOfAddressException.cpp exceptions/OutOfAddressException.h
        exceptions/InvalidArgumentException.cpp exceptions/InvalidArgumentException.h
        exceptions/SocketException.cpp exceptions/SocketException.h
        request/Ack.cpp request/Ack.h request/Nack.cpp request/Nack.h)


add_executable(isa_proj ${PROGRAM_FILES})
add_executable(tests ${TEST_FILES})
