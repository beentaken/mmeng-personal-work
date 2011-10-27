cmake_minimum_required(VERSION 2.6)
project(CS260)

find_package(Boost 1.46.0 COMPONENTS thread REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})
if (MSVC)
    # Whatever
else ()
    set(CMAKE_C_FLAGS "-Wextra -Wall -std=c99 -pedantic")
    set(CMAKE_C_FLAGS_DEBUG "-g")
    set(CMAKE_C_FLAGS_RELEASE "-O2")

    set(CMAKE_CXX_FLAGS "-Wextra -Wall -std=c++0x -pedantic -pipe")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
endif ()

set(SERVER_SOURCES server.cpp network.cpp chess.cpp)
set(CLIENT_SOURCES client.cpp network.cpp)

add_executable(server ${SERVER_SOURCES})
add_executable(client ${CLIENT_SOURCES})
target_link_libraries(client ${Boost_LIBRARIES})

