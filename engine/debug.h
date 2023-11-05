#pragma once
#include <stdio.h>


#if 1
//DEFINE THIS OUTSIDE THIS FILE AND BEFORE INCLUDING the engine to remove the output
//#define Debug_NO_OUTPUT

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


#ifndef Debug_NO_OUTPUT

#define Debug_LOG(...) {printf(ANSI_COLOR_YELLOW "[LOG] " ANSI_COLOR_RESET __VA_ARGS__); printf("\n");}
#define Debug_ERROR(...) {printf(ANSI_COLOR_RED "[ERROR] " ANSI_COLOR_BLUE "%s:%i in %s: " ANSI_COLOR_RESET, __FILE__, __LINE__, __FUNCTION__); printf(__VA_ARGS__); printf("\n");}

#define Debug_TEST(condition)\
if(condition) \
printf(ANSI_COLOR_GREEN "[TEST PASSED]" ANSI_COLOR_BLUE " %s:%i in %s: " ANSI_COLOR_GREEN #condition ANSI_COLOR_RESET "\n", __FILE__, __LINE__, __FUNCTION__);\
else \
printf(ANSI_COLOR_RED "[TEST FAILED]" ANSI_COLOR_BLUE " %s:%i in %s: " ANSI_COLOR_RED #condition ANSI_COLOR_RESET "\n", __FILE__, __LINE__, __FUNCTION__);

#else
#define Debug_LOG(...);
#define Debug_ERROR(...);
#define Debug_TEST(condition);
#endif
#endif