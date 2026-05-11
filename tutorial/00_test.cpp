/*

g++ 00_test.cpp -o ../bin/00_test.exe -I../src -std=gnu++17 -Wall

nc -U -l -k /tmp/debug_print.socket

*/

//----------------------------------------------------------------------

#include "utils.h"

int  main()
{
    debug_print("hello world!\n");
}
