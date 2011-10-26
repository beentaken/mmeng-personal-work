cmake_minimum_required(VERSION 2.6)
project(CS260)

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

set(SERVER_SOURCES server.cpp network.cpp)
set(CLIENT_SOURCES client.cpp network.cpp)

add_executable(server ${SERVER_SOURCES})
add_executable(client ${CLIENT_SOURCES})

