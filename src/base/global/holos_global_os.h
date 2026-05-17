
#ifndef holos_global_os_included
#define holos_global_os_included
//----------------------------------------------------------------------

#if defined HOLOS_LINUX
    #include "base/global/os/holos_global_os_linux.h"
#elif defined HOLOS_WIN32
    #include "base/global/os/holos_global_os_win32.h"
#elif defined HOLOS_MAC
    #include "base/global/os/holos_global_os_mac.h"
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
#endif // holos_global_os_included
