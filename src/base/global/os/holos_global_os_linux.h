#ifndef holos_global_os_linux_included
#define holos_global_os_linux_included
//----------------------------------------------------------------------

// #include <stdarg.h>
// #include <stdint.h>
// #include <stdio.h>
// #include <string.h>

//----------

#include "base/global/holos_global_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class HOLOS_GlobalOS
{
    friend class HOLOS_Global;
    public:
        HOLOS_GlobalOS(HOLOS_GlobalBase* AGlobal);
        ~HOLOS_GlobalOS();
    private:
        void        initialize();
        void        cleanup();
    private:
        HOLOS_GlobalBase*   MGlobal = nullptr;
};

//----------------------------------------------------------------------

HOLOS_GlobalOS::HOLOS_GlobalOS(HOLOS_GlobalBase* AGlobal)
{
    MGlobal = AGlobal;
}

HOLOS_GlobalOS::~HOLOS_GlobalOS()
{
}

//------------------------------
//
//------------------------------

void HOLOS_GlobalOS::initialize()
{
    HOLOS_BasePrint("\n");
}

void HOLOS_GlobalOS::cleanup()
{
    HOLOS_BasePrint("\n");
}

//----------------------------------------------------------------------
#endif // holos_global_os_linux_included
