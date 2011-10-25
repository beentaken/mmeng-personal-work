# Linked lists lab.
cmake_minimum_required(VERSION 2.6)
project(FUNCTIONS)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-O -Wextra -Wall -ansi -pedantic -g")
elseif(MSVC)
	set(CMAKE_CXX_FLAGS "/EHa /W4 /WX /Za")
elseif(BORLAND)
	set(CMAKE_CXX_FLAGS "-w")
endif(CMAKE_COMPILER_IS_GNUCXX)

add_executable(funs-sample driver-sample.cpp)
add_executable(funs-stress driver-stress.cpp)

enable_testing()
add_test(SAMPLE_DIFF ${PROJECT_SOURCE_DIR}/difftest.sh funs-sample ./myoutput-sample.txt ${PROJECT_SOURCE_DIR}/output-sample.txt)
add_test(STRESS_DIFF ${PROJECT_SOURCE_DIR}/difftest.sh funs-stress ./myoutput-stress.txt ${PROJECT_SOURCE_DIR}/output-stress.txt)

