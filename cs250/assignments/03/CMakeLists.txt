cmake_minimum_required(VERSION 2.6)
project(CS250)

set(EXEC_NAME "driver")

find_package(GLUT REQUIRED)

if (WIN32)
if (NOT GLUT_INCLUDE_DIRS)
	set(GLUT_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/dependancies/glut/include)
endif(NOT GLUT_INCLUDE_DIRS)

#if (NOT GLUT_LIBRARIES)
    set(GLUT_LIBRARIES ${PROJECT_SOURCE_DIR}/dependancies/glut/lib/glut32.lib)
	message("GLUT_LIBRARIES set to ${GLUT_LIBRARIES}")
#endif(NOT GLUT_LIBRARIES)
endif(WIN32)

include_directories(${GLUT_INCLUDE_DIRS})
#set(LIBS ${LIBS} ${GLUT_LIBRARIES} ${GLUT_glut_LIBRARY})
set(LIBS ${LIBS} ${GLUT_glut_LIBRARY})

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
    set(CMAKE_CXX_FLAGS "-Wextra -Wall -std=c++0x -fdiagnostics-show-option")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif(MSVC)

#file(GLOB SOURCES *.cpp)
set(SOURCES Utilities.cpp assignment.cpp Vector4.cpp Matrix4.cpp
    Point4.cpp render.cpp box.cpp transformations.cpp parser.cpp camera.cpp)

add_executable(${EXEC_NAME} main.cpp ${SOURCES})
target_link_libraries(${EXEC_NAME} ${LIBS})

add_executable(parser_test parser_test.cpp parser.cpp Vector4.cpp Point4.cpp)

