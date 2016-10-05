cmake_minimum_required(VERSION 3.6)
project(isa_proj)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp adressing/IpAddress.cpp adressing/IpAddress.h adressing/MacAddress.cpp adressing/MacAddress.h adressing/Timestamp.cpp adressing/Timestamp.h adressing/Reservation.cpp adressing/Reservation.h adressing/AddressPool.cpp adressing/AddressPool.h adressing/AddressHandler.cpp adressing/AddressHandler.h BaseObject.h)
add_executable(isa_proj ${SOURCE_FILES})