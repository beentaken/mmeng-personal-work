# CS280 Assignment 01: Fixed-Size Memory Manager.
cmake_minimum_required(VERSION 2.6)
project(MEM_MANAGER)

set(EXEC_NAME "mem_manager")

# Set a default build type for single-configuration
# CMake generators if no build type is set.
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE RelWithDebInfo)
endif(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-Wextra -Wall -Wconversion -ansi -pedantic")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
elseif(MSVC)
	set(CMAKE_CXX_FLAGS "/EHa /MTd /W4 /WX /Za /D_CRT_SECURE_NO_DEPRECATE")
elseif(BORLAND)
	set(CMAKE_CXX_FLAGS "-w -vG -v -w-8026")
endif(CMAKE_COMPILER_IS_GNUCXX)

add_executable(${EXEC_NAME}1 driver-sample.cpp ObjectAllocator.cpp PRNG.cpp)
add_executable(${EXEC_NAME}2 driver-sample2.cpp ObjectAllocator.cpp PRNG.cpp)

#enable_testing()

set(DIFFTEST ${PROJECT_SOURCE_DIR}/difftest.sh)
set(MEMTEST ${PROJECT_SOURCE_DIR}/memtest.sh)

add_test(TEST_0 ${DIFFEST} ./${EXEC_NAME} ${CURRENT_TEST} ${PROJECT_SOURCE_DIR}/out${CURRENT_TEST})

#foreach(CURRENT_TEST RANGE 0 7)
#	add_test(TEST_${CURRENT_TEST} ${DIFFEST} ./${EXEC_NAME} ${CURRENT_TEST} ${PROJECT_SOURCE_DIR}/out${CURRENT_TEST})
#	add_test(MEM_${CURRENT_TEST} ${MEMTEST} ./${EXEC_NAME} ${CURRENT_TEST})
#endforeach(CURRENT_TEST)

