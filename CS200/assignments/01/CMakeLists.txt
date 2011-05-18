cmake_minimum_required(VERSION 2.6)
project(CS200)

set(EXEC_NAME "driver")

find_package(GLUT REQUIRED)

if (NOT GLUT_INCLUDE_DIRS)
	set(GLUT_INCLUDE_DIRS ${PROJECT_SOURCE_DIR})
endif(NOT GLUT_INCLUDE_DIRS)

include_directories(${GLUT_INCLUDE_DIRS})
set(LIBS ${LIBS} ${GLUT_LIBRARIES})

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
#	set(CMAKE_CXX_FLAGS_DEBUG "/EHa /W4 /Za /WX /D_CRT_SECURE_NO_DEPRECATE")
#	set(CMAKE_CXX_FLAGS_RELEASE "/O2 /MT /EHa /W4 /Za /WX /D_CRT_SECURE_NO_DEPRECATE")
elseif(BORLAND)
	set(CMAKE_CXX_FLAGS_DEBUG "-v -vG -w -w-8026 -w-8091")
endif(CMAKE_COMPILER_IS_GNUCXX)

#file(GLOB SOURCES *.cpp)
set(SOURCES Utilities.cpp line.cpp assignment01.cpp)

add_executable(${EXEC_NAME} main.cpp ${SOURCES})
target_link_libraries(${EXEC_NAME} ${LIBS})
#add_executable(${EXEC_NAME}2 driver-sample-dh.cpp ${SOURCES})
#add_executable(${EXEC_NAME}3 driver-sample2.cpp ${SOURCES})

#enable_testing()

set(DIFFTEST ${PROJECT_SOURCE_DIR}/difftest.sh)
set(MEMTEST ${PROJECT_SOURCE_DIR}/memtest.sh)

foreach(CURRENT_TEST RANGE 1 3)
	add_test(TEST_${CURRENT_TEST} ${DIFFEST} "./${EXEC_NAME}${CURRENT_TEST}" "${PROJECT_SOURCE_DIR}/out${CURRENT_TEST}")
	if(UNIX)
		add_test(MEM_${CURRENT_TEST} ${MEMTEST} "./${EXEC_NAME}${CURRENT_TEST}")
	endif(UNIX)
endforeach(CURRENT_TEST)

