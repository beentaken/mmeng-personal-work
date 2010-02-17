# Linked lists lab.
cmake_minimum_required(VERSION 2.6)
project(POINT)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-Wextra -Wall -ansi -pedantic -O")
elseif(MSVC)
	set(CMAKE_CXX_FLAGS "/EHa /W4 /WX /Za")
elseif(BORLAND)
	set(CMAKE_CXX_FLAGS "-w")
endif(CMAKE_COMPILER_IS_GNUCXX)

add_executable(points Point.cpp driver-sample.cpp)

enable_testing()
add_test(BASIC_DIFF difftest.sh ./points myoutput.txt output-sample.txt)

