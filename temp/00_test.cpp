/*
    compile:
        g++ 00_test.cpp -o 00_test.exe -I../src -std=gnu++17 -Wall
    print debug_print output:
        nc -U -l -k /tmp/debug_print.socket    
*/

#include "utils.h"

int  main()
{
    debug_print("hello world!\n");
}