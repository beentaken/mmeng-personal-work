# Linked lists lab.
cmake_minimum_required(VERSION 2.6)
project(VECTOR)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-O -Wextra -Wall -ansi -pedantic -g")
elseif(MSVC)
	set(CMAKE_CXX_FLAGS "/EHa /W4 /WX /Za")
elseif(BORLAND)
	set(CMAKE_CXX_FLAGS "-w")
endif(CMAKE_COMPILER_IS_GNUCXX)

add_executable(vector Vector.cpp main.cpp)

enable_testing()
add_test(BASIC_DIFF ${PROJECT_SOURCE_DIR}/difftest.sh vector ./myoutput.txt ${PROJECT_SOURCE_DIR}/output-all.txt)

