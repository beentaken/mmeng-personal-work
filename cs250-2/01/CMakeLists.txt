cmake_minimum_required(VERSION 2.6)
project(CS250 CXX)

if (MSVC)
    # Whatever
    set(CMAKE_CXX_FLAGS "/EHsc /W4")
    set(CMAKE_EXE_LINKER_FLAGS "/subsystem:windows")
else ()
    set(CMAKE_C_FLAGS "-Wextra -Wall -std=c99 -pedantic")
    set(CMAKE_C_FLAGS_DEBUG "-g")
    set(CMAKE_C_FLAGS_RELEASE "-O2")

    set(CMAKE_CXX_FLAGS "-Wextra -Wall -std=c++0x -pedantic -pipe -m32")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
    set(CMAKE_CXX_LINK_FLAGS "-mwindows")
endif ()

set(HEADERS cs250vector.h assignment.hpp draw.hpp)
set(SOURCES win_demo.cpp cs250vector.cpp assignment.cpp draw.cpp)

add_executable(driver ${SOURCES} ${HEADERS})
target_link_libraries(driver gdi32 user32 gdiplus winmm)
set_target_properties(driver PROPERTIES CLEAN_DIRECT_OUTPUT 1)

