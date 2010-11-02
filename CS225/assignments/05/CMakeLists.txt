# BST-based print_queue assignment.
cmake_minimum_required(VERSION 2.6)
project(PRINT_QUEUE)

set(CMAKE_C_FLAGS "-Wextra -Wall -std=c89 -pedantic -Wstrict-prototypes -Wmissing-prototypes -Wdeclaration-after-statement -pipe -g")
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -ansi -pedantic -Weffc++ -g -pipe")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -ansi -pedantic -g -pipe")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O")

add_executable(print_queue driver.cpp print_queue.cpp printjob.cpp)

enable_testing()

set(DIFFTEST ${PROJECT_SOURCE_DIR}/difftest.sh)
set(MEMTEST ${PROJECT_SOURCE_DIR}/memtest.sh)

foreach(CURRENT_TEST RANGE 0 7)
	add_test(TEST_${CURRENT_TEST} ${DIFFEST} ./print_queue ${CURRENT_TEST} ${PROJECT_SOURCE_DIR}/out${CURRENT_TEST})
	add_test(MEM_${CURRENT_TEST} ${MEMTEST} ./print_queue ${CURRENT_TEST})
endforeach(CURRENT_TEST)

#add_test(TEST_0 ${PROJECT_SOURCE_DIR}/difftest.sh ./print_queue 0 ${PROJECT_SOURCE_DIR}/out0)
#add_test(TEST_1 ${PROJECT_SOURCE_DIR}/difftest.sh ./print_queue 1 ${PROJECT_SOURCE_DIR}/out1)
#add_test(TEST_2 ${PROJECT_SOURCE_DIR}/difftest.sh ./print_queue 2 ${PROJECT_SOURCE_DIR}/out2)
#add_test(TEST_3 ${PROJECT_SOURCE_DIR}/difftest.sh ./print_queue 3 ${PROJECT_SOURCE_DIR}/out3)
#add_test(TEST_4 ${PROJECT_SOURCE_DIR}/difftest.sh ./print_queue 4 ${PROJECT_SOURCE_DIR}/out4)
#add_test(TEST_5 ${PROJECT_SOURCE_DIR}/difftest.sh ./print_queue 5 ${PROJECT_SOURCE_DIR}/out5)
#add_test(TEST_6 ${PROJECT_SOURCE_DIR}/difftest.sh ./print_queue 6 ${PROJECT_SOURCE_DIR}/out6)
#add_test(TEST_7 ${PROJECT_SOURCE_DIR}/difftest.sh ./print_queue 7 ${PROJECT_SOURCE_DIR}/out7)
#add_test(MEM_0 ${PROJECT_SOURCE_DIR}/memtest.sh ./print_queue 0)
#add_test(MEM_1 ${PROJECT_SOURCE_DIR}/memtest.sh ./print_queue 1)
#add_test(MEM_2 ${PROJECT_SOURCE_DIR}/memtest.sh ./print_queue 2)
#add_test(MEM_3 ${PROJECT_SOURCE_DIR}/memtest.sh ./print_queue 3)
#add_test(MEM_4 ${PROJECT_SOURCE_DIR}/memtest.sh ./print_queue 4)
#add_test(MEM_5 ${PROJECT_SOURCE_DIR}/memtest.sh ./print_queue 5)
#add_test(MEM_6 ${PROJECT_SOURCE_DIR}/memtest.sh ./print_queue 6)
#add_test(MEM_7 ${PROJECT_SOURCE_DIR}/memtest.sh ./print_queue 7)

