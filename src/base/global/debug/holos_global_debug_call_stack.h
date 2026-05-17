#ifndef holos_global_debug_call_stack_included
#define holos_global_debug_call_stack_included
//----------------------------------------------------------------------

#include <stdint.h>
//#include <stdio.h>
#include <stdlib.h>
//#include <memory.h>

#include <new>

//----------

#include "base/global/holos_global_base.h"
#include "base/global/debug/holos_global_debug_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class HOLOS_GlobalDebugCallStack
{
    friend class HOLOS_GlobalDebug;
    public:
        HOLOS_GlobalDebugCallStack(HOLOS_GlobalDebugBase* AGlobalDebug);
        ~HOLOS_GlobalDebugCallStack();
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

// note: Global->PRINT not initialized yet

HOLOS_GlobalDebugCallStack::HOLOS_GlobalDebugCallStack(HOLOS_GlobalDebugBase* AGlobalDebug)
{
    MGlobalDebug = AGlobalDebug;
    MGlobal = MGlobalDebug->getGlobal();
}

HOLOS_GlobalDebugCallStack::~HOLOS_GlobalDebugCallStack()
{
}

//------------------------------
//
//------------------------------

void HOLOS_GlobalDebugCallStack::initialize()
{
    HOLOS_BasePrint("\n");
}

void HOLOS_GlobalDebugCallStack::cleanup()
{
    HOLOS_BasePrint("\n");
}

//------------------------------
//
//------------------------------

//----------------------------------------------------------------------
#endif // holos_global_debug_call_stack_included