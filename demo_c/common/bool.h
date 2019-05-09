#ifndef _COMMON_BOOL_H_
#define _COMMON_BOOL_H_

    #ifndef TRUE
    #define TRUE    1
    #endif

    #ifndef FALSE
    #define FALSE   0
    #endif

    #ifndef BOOL
    typedef int     BOOL;
    #endif

    #define BOOL_STR(...)   ((__VA_ARGS__)? "TRUE" : "FALSE")

#endif