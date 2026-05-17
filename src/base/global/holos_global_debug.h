#ifndef holos_global_debug_included
#define holos_global_debug_included
//----------------------------------------------------------------------

#include "base/global/debug/holos_global_debug_base.h"

#include "base/global/debug/holos_global_debug_assert.h"
#include "base/global/debug/holos_global_debug_call_stack.h"
#include "base/global/debug/holos_global_debug_crash_handler.h"
#include "base/global/debug/holos_global_debug_mem_tracer.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class HOLOS_GlobalDebug
: public HOLOS_GlobalDebugBase
{
    friend class HOLOS_Global;
    public:
        HOLOS_GlobalDebug(HOLOS_GlobalBase* AGlobal);
        ~HOLOS_GlobalDebug();
    private:
        void    initialize();
        void    cleanup();
    private:
        bool    MInitialized    = false;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

// note: AGlobal->PRINT not initialized yet

HOLOS_GlobalDebug::HOLOS_GlobalDebug(HOLOS_GlobalBase* AGlobal)
: HOLOS_GlobalDebugBase(AGlobal)
{
    CALL_STACK      = new HOLOS_GlobalDebugCallStack(this);
    CRASH_HANDLER   = new HOLOS_GlobalDebugCrashHandler(this);
    MEM_TRACER      = new HOLOS_GlobalDebugMemTracer(this);
}

HOLOS_GlobalDebug::~HOLOS_GlobalDebug()
{
    if (MEM_TRACER)     delete MEM_TRACER;
    if (CRASH_HANDLER)  delete CRASH_HANDLER;
    if (CALL_STACK)     delete CALL_STACK;
}

//------------------------------
//
//------------------------------

void HOLOS_GlobalDebug::initialize()
{
    HOLOS_BasePrint("\n");
    if (!MInitialized)
    {
        CALL_STACK->initialize();
        CRASH_HANDLER->initialize();
        MEM_TRACER->initialize();
        MInitialized = true;
    }
}

void HOLOS_GlobalDebug::cleanup()
{
    HOLOS_BasePrint("\n");
    if (MInitialized)
    {
        MEM_TRACER->cleanup();
        CRASH_HANDLER->cleanup();
        CALL_STACK->cleanup();
        MInitialized = false;
    }
}

//----------------------------------------------------------------------
#endif // holos_global_debug_included
