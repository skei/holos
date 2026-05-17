#ifndef holos_defines_included
#define holos_defines_included
//----------------------------------------------------------------------

#if defined (__gnu_linux__)
    #define HOLOS_LINUX
#endif

#if defined (_WIN32) || (__MINGW32__)
    #define  HOLOS_WIN32
#endif

// TODO: HOLOS_MAC

//----------

#if defined (__i386__) || defined (_X86_) || defined (__X86__)
    #define HOLOS_32BIT
#endif

#if defined (__x86_64) || (__LP64__)
    #define HOLOS_64BIT
#endif

//----------

#if (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
    #define HOLOS_BIG_ENDIAN
#endif

#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
    #define HOLOS_LITTLE_ENDIAN
#endif

//----------

//#if defined ( __GNUC__)
//    #define HOLOS_GCC
//#endif

//#if (__cplusplus >= 201103L)
//    #define HOLOS_CPP11
//#endif

//----------------------------------------------------------------------
#endif // holos_defines_included
