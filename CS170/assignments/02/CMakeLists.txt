# Linked lists lab.
cmake_minimum_required(VERSION 2.6)
project(WARBOATS)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-Wextra -Wall -ansi -pedantic")
elseif(MSVC)
	set(CMAKE_CXX_FLAGS "/EHa /W4 /WX /Za")
elseif(BORLAND)
	set(CMAKE_CXX_FLAGS "-w")
endif(CMAKE_COMPILER_IS_GNUCXX)

add_executable(warboats PRNG.cpp Ocean.cpp driver-big.cpp)

