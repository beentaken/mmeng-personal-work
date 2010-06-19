/* version 1.2
 * change from 1.1
 * 		support for ENTER_LEAVE
 * 		support for log_it_mark_line
 * Wed 03 Jun 2009 12:58:47 PM PDT
 * Dmitri Volper
 */
/* Using logging:
To do nothing:
//#define FUNCTION_LOG "LOG"
#include "logging_macros.h"

each function call is logged and final stats displayed:
#define FUNCTION_LOG "LOG"
#include "logging_macros.h"

final stats only:
#define FUNCTION_LOG "LOG"
#define NO_ENTER_LEAVE
#include "logging_macros.h"

To enable logging of a function add
log_it(std::cout);
in the beginning of function (std::cerr, or any other stream)
Example:
void foo() {
	log_it(std::cout);
	.....
	.....
	.....
}

log_it_mark_line(x); 
will outputs a line with file and line number information - 
makes it easer to find a particular place where function breaks.
May be used anywhere and any number of times in the function.

Example output:
LOG enter CS225::Map::Map_iterator::Map_iterator(CS225::Map::Node*) (map.cpp +181)
LOG leaving CS225::Map::Map_iterator::Map_iterator(CS225::Map::Node*) (map.cpp) 660
LOG enter CS225::Map::Map_iterator_const::Map_iterator_const(CS225::Map::Node*) (map.cpp +250)
LOG leaving CS225::Map::Map_iterator_const::Map_iterator_const(CS225::Map::Node*) (map.cpp) 636
....
LOG Statistics for CS225::Map::Node* CS225::Map::Node::decrement()   (map.cpp +374)
LOG      called 6 times
LOG      average time 121573

660 and 636 and 121573 are in CPU ticks (thus independent of the CPU speed)


*/

//this file may be read several times in the same translation unit
//to avoid "re-definition" of macros - undefine them first
#undef log_it
#undef log_it_mark_line

//if defined, generate code to create statistics objects
//otherwise do nothing
#ifdef FUNCTION_LOG 
#include <string>
#include "cycle.h"
#include "logging.h"

#ifdef __GNUC__
#define __MY_FUNCTION__  __PRETTY_FUNCTION__
#else
#define __MY_FUNCTION__  __FUNCTION__
#endif

#ifdef __GNUC__
#warning "INFO - Logging methods from" 
#endif

#ifdef _MSC_VER
#pragma message("Warning: INFO - Logging methods from")
#endif

#define log_it_mark_line(x) \
	x << "---- " << __FILE__ << " +" << __LINE__ << " -------------\n";

//user may set "NO_ENTER_LEAVE" to print final stats only
//if user didn't specify NO_ENTER_LEAVE, assume the enter/leave function output is desired
#ifndef NO_ENTER_LEAVE
#define log_it(x) \
static LOGGING::LOG_STATISTICS __statistics__you_better_not_use_this_name_anyhere_else( \
		__MY_FUNCTION__, \
		__FILE__, \
		__LINE__, \
		x); \
LOGGING::LOG_CLASS __you_better_not_use_this_name_anyhere_else( \
		__MY_FUNCTION__, \
		__FILE__, \
		__LINE__, \
		x, \
		__statistics__you_better_not_use_this_name_anyhere_else, \
		true)
#else
#define log_it(x) \
static LOGGING::LOG_STATISTICS __statistics__you_better_not_use_this_name_anyhere_else( \
		__MY_FUNCTION__, \
		__FILE__, \
		__LINE__, \
		x); \
LOGGING::LOG_CLASS __you_better_not_use_this_name_anyhere_else( \
		__MY_FUNCTION__, \
		__FILE__, \
		__LINE__, \
		x, \
		__statistics__you_better_not_use_this_name_anyhere_else, \
		false)
#endif


#else // FUNCTION_LOG not defined - do nothing
#define log_it(x) 
#define log_it_mark_line(x) 
#endif

//this file may be read several times in the same translation unit
#undef FUNCTION_LOG
#undef NO_ENTER_LEAVE

/*
First of all - the main purposes of this macros:
1) simple profiling
2) simple debugging

logging uses the fact that in C++ local function objects are deleted in the
end of function execution (unlike Java,C# with their garbage collectors).
All "log_it(x);" does is insert an object of type LOGGING::LOG_CLASS
(logging.h) in the beginning of the corresponding function. Object's ctor and
dtor start and stop timer, dtor will also calculate the difference and send
it to a static object that collects statistics for this function of type
LOGGING::LOG_STATISTICS (logging.h).

Objects are defined in logging.h 
Macros  are defined in logging_macros.h (this file)

Arguments of LOG_CLASS: 
__MY_FUNCTION__ macro (so compiler evaluates it) function signature - will look different on different compilers.  
__FILE__ macro file name  (compiler)
__LINE__ macro line number  (compiler)
x output stream (user)

"LOG" is just a marker to distinguish regular program output and logging
output - you may change it.

===========

A general note about macros: they are evil.  Debugging is very difficult
since you do not see the intermediate step after compiler is done
substituting macros with C++ code, therefore some of the errors don't make
sense. Some of those problem may be solved by forcing the compiler to show
C++ code after macro substitution step: use 
g++ -E file_with_macros.cpp > file_with_macros.preprocessed.cpp
*/
