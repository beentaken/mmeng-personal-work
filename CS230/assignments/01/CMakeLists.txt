cmake_minimum_required(VERSION 2.6)
project(CS200)

set(EXEC_NAME "driver")

# Set a default build type for single-configuration
# CMake generators if no build type is set.
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE RelWithDebInfo)
endif(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

if(CMAKE_COMPILER_IS_GNUCC)
	#	set(CMAKE_CXX_FLAGS "-Wextra -Wall -Wconversion -ansi -pedantic")
	set(CMAKE_C_FLAGS_RELWITHDEBINFO "-Wextra -Wall -ansi -pedantic -O2 -g")
	set(CMAKE_C_FLAGS_RELEASE "-O2 -Wextra -Wall -ansi -pedantic")
	set(CMAKE_C_FLAGS_DEBUG "-g -Wextra -Wall -ansi -pedantic")
elseif(MSVC)
    #	set(CMAKE_CXX_FLAGS_DEBUG "/EHa /W4 /Za /WX /D_CRT_SECURE_NO_DEPRECATE")
    #set(CMAKE_CXX_FLAGS_RELEASE "/O2 /MT /EHa /W4 /Za /WX /D_CRT_SECURE_NO_DEPRECATE")
    set(CMAKE_CXX_FLAGS_DEBUG "-D_SCL_SECURE_NO_WARNINGS")
elseif(BORLAND)
	set(CMAKE_CXX_FLAGS_DEBUG "-v -vG -w -w-8026 -w-8091")
endif(CMAKE_COMPILER_IS_GNUCC)

file(GLOB SOURCES *.c)
#set(SOURCES main.c)

add_executable(${EXEC_NAME} ${SOURCES})
#target_link_libraries(${EXEC_NAME} ${LIBS})

