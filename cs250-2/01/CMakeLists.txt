cmake_minimum_required(VERSION 2.6)
project(CS250 CXX)

if (MSVC)
    # Whatever
else ()
    set(CMAKE_C_FLAGS "-Wextra -Wall -std=c99 -pedantic")
    set(CMAKE_C_FLAGS_DEBUG "-g")
    set(CMAKE_C_FLAGS_RELEASE "-O2")

    set(CMAKE_CXX_FLAGS "-Wextra -Wall -std=c++0x -pedantic -pipe -m32")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
    set(CMAKE_CXX_LINK_FLAGS "-mwindows")
endif ()

set(SOURCES win_demo.cpp cs250vector.cpp)

add_executable(driver ${SOURCES})
target_link_libraries(driver gdi32 user32)
set_target_properties(driver PROPERTIES CLEAN_DIRECT_OUTPUT 1)

