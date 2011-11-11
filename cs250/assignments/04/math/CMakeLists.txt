cmake_minimum_required(VERSION 2.6)
project(CS250_MATH CXX)

# Set a default build type for single-configuration
# CMake generators if no build type is set.
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE RelWithDebInfo)
endif(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

if(MSVC)
    #	set(CMAKE_CXX_FLAGS_DEBUG "/EHa /W4 /Za /WX /D_CRT_SECURE_NO_DEPRECATE")
    #set(CMAKE_CXX_FLAGS_RELEASE "/O2 /MT /EHa /W4 /Za /WX /D_CRT_SECURE_NO_DEPRECATE")
    #set(CMAKE_CXX_FLAGS "/EHa /W4 /Za")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
elseif(BORLAND)
    # Good god I hope this never gets used.
	set(CMAKE_CXX_FLAGS_DEBUG "-v -vG -w -w-8026 -w-8091")
else(MSVC)
    # g++, clang++, etc
    # can't pedantic because of Patrick's anonymous structs
    set(CMAKE_CXX_FLAGS "-Wextra -Wall -std=c++0x  -fdiagnostics-show-option")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif(MSVC)

#file(GLOB SOURCES *.cpp)
set(SOURCES Matrix4.cpp Point4.cpp Vector4.cpp)

add_library(cs250_math STATIC ${SOURCES})

