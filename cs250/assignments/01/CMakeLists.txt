cmake_minimum_required(VERSION 2.6)
project(CS250)

set(CMAKE_CXX_FLAGS "-Wextra -Wall -ansi -pipe -g")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O")

set(SOURCES Matrix4.cpp Vector4.cpp Point4.cpp sample-driver.cpp)
add_executable(basic ${SOURCES})
#target_link_libraries(basic ${OPENGL_LIBRARIES} ${X11_LIBRARIES} ${PNG_LIBRARIES} ${FMOD_LIBRARIES} ${OIS_LIBRARIES})

