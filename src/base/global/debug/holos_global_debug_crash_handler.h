#ifndef holos_global_debug_crash_handler_included
#define holos_global_debug_crash_handler_included
//----------------------------------------------------------------------

// #include <stdint.h>
// //#include <stdio.h>
// #include <stdlib.h>
// //#include <memory.h>
// #include <new>

// #include "base/holos_base.h"
#include "base/global/holos_global_base.h"
#include "base/global/debug/holos_global_debug_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class HOLOS_GlobalDebugCrashHandler
{
    friend class HOLOS_GlobalDebug;
    public:
        HOLOS_GlobalDebugCrashHandler(HOLOS_GlobalDebugBase* AGlobalDebug);
        ~HOLOS_GlobalDebugCrashHandler();
    public:
    private:
        void        initialize();
        void        cleanup();
    private:
        HOLOS_GlobalBase*       MGlobal         = nullptr;
        HOLOS_GlobalDebugBase*  MGlobalDebug    = nullptr;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

HOLOS_GlobalDebugCrashHandler::HOLOS_GlobalDebugCrashHandler(HOLOS_GlobalDebugBase* AGlobalDebug)
{
    MGlobalDebug = AGlobalDebug;
    MGlobal = MGlobalDebug->getGlobal();
}

HOLOS_GlobalDebugCrashHandler::~HOLOS_GlobalDebugCrashHandler()
{
}

//------------------------------
//
//------------------------------

void HOLOS_GlobalDebugCrashHandler::initialize()
{
    HOLOS_BasePrint("\n");
}

void HOLOS_GlobalDebugCrashHandler::cleanup()
{
    HOLOS_BasePrint("\n");
}

//------------------------------
//
//------------------------------

//----------------------------------------------------------------------
#endif // holos_global_debug_crash_handler_included