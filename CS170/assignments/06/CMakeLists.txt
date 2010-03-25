# Linked lists lab.
cmake_minimum_required(VERSION 2.6)
project(LINKEDLIST)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-O -Wextra -Wall -ansi -pedantic -g")
elseif(MSVC)
	set(CMAKE_CXX_FLAGS "/EHa /W4 /WX /Za")
elseif(BORLAND)
	set(CMAKE_CXX_FLAGS "-w")
endif(CMAKE_COMPILER_IS_GNUCXX)

add_executable(ll-sample driver-sample.cpp)
add_executable(ll-sample-person driver-sample-person.cpp)
add_executable(ll-stress driver-stress.cpp)

enable_testing()
add_test(SAMPLE_DIFF ${PROJECT_SOURCE_DIR}/difftest.sh ll-sample ./myoutput-sample.txt ${PROJECT_SOURCE_DIR}/output-sample.txt)
add_test(PERSON_DIFF ${PROJECT_SOURCE_DIR}/difftest.sh ll-sample-person ./myouput-sample-person.txt ${PROJECT_SOURCE_DIR}/output-sample-person.txt)
add_test(STRESS_DIFF ${PROJECT_SOURCE_DIR}/difftest.sh ll-stress ./myoutput-stress.txt ${PROJECT_SOURCE_DIR}/output-stress2.txt)

