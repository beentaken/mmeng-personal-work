cmake_minimum_required(VERSION 2.6)
project(MEMMANAGER)

set(CMAKE_C_FLAGS "-Wextra -Wall -std=c89 -pedantic -Wstrict-prototypes -Wmissing-prototypes -Wdeclaration-after-statement -pipe -g")
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -ansi -pedantic -Weffc++ -g -pipe")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -ansi -pedantic -g -pipe")
##set(CMAKE_CXX_FLAGS "-Wall -Wextra -ansi -pedantic -g -pipe")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O")

add_executable(mm MMtest.cpp MemoryManager.cpp)

enable_testing()
add_test(TEST_0 ${PROJECT_SOURCE_DIR}/difftest.sh ./mm ${PROJECT_SOURCE_DIR}/MMtest.txt)
add_test(MEM_0 ${PROJECT_SOURCE_DIR}/memtest.sh ./mm)

