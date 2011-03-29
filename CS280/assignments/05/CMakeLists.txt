cmake_minimum_required(VERSION 2.6)
project(HASHTABLE)

set(EXEC_NAME "ht")

# Set a default build type for single-configuration
# CMake generators if no build type is set.
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE RelWithDebInfo)
endif(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

if(CMAKE_COMPILER_IS_GNUCXX)
	#	set(CMAKE_CXX_FLAGS "-Wextra -Wall -Wconversion -ansi -pedantic")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Wextra -Wall -Wconversion -ansi -pedantic -O2 -g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wextra -Wall -Wconversion -ansi -pedantic")
	set(CMAKE_CXX_FLAGS_DEBUG "-g -Wextra -Wall -Wconversion -ansi -pedantic")
elseif(MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG "/EHa /W4 /Za /WX /D_CRT_SECURE_NO_DEPRECATE")
	set(CMAKE_CXX_FLAGS_RELEASE "/O2 /MT /EHa /W4 /Za /WX /D_CRT_SECURE_NO_DEPRECATE")
elseif(BORLAND)
	set(CMAKE_CXX_FLAGS_DEBUG "-v -vG -w -w-8026 -w-8091")
endif(CMAKE_COMPILER_IS_GNUCXX)

#file(GLOB SOURCES *.cpp)
set(SOURCES OAHashTable.cpp Support.cpp)

add_executable(${EXEC_NAME}1 driver-sample.cpp ${SOURCES})
add_executable(${EXEC_NAME}2 driver-sample2.cpp ${SOURCES})

#enable_testing()

set(DIFFTEST ${PROJECT_SOURCE_DIR}/difftest.sh)
set(MEMTEST ${PROJECT_SOURCE_DIR}/memtest.sh)

add_test(TEST_0 ${DIFFEST} ./${EXEC_NAME} ${CURRENT_TEST} ${PROJECT_SOURCE_DIR}/out${CURRENT_TEST})

#foreach(CURRENT_TEST RANGE 0 7)
#	add_test(TEST_${CURRENT_TEST} ${DIFFEST} ./${EXEC_NAME} ${CURRENT_TEST} ${PROJECT_SOURCE_DIR}/out${CURRENT_TEST})
#	add_test(MEM_${CURRENT_TEST} ${MEMTEST} ./${EXEC_NAME} ${CURRENT_TEST})
#endforeach(CURRENT_TEST)

