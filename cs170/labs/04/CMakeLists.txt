# Linked lists lab.
cmake_minimum_required(VERSION 2.6)
project(LINKEDLISTS)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-Wextra -Wall -ansi -pedantic")
elseif(MSVC)
	set(CMAKE_CXX_FLAGS "/EHa /W4 /WX /Za")
elseif(BORLAND)
	set(CMAKE_CXX_FLAGS "-w")
endif(CMAKE_COMPILER_IS_GNUCXX)

add_executable(ll list.cpp main.cpp)

enable_testing()
add_test(BASIC_DIFF difftest.sh ./ll myoutput.txt output-all.txt)

