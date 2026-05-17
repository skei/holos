#ifndef holos_global_debug_base_included
#define holos_global_debug_base_included
//----------------------------------------------------------------------

class HOLOS_GlobalDebugCallStack;
class HOLOS_GlobalDebugCrashHandler;
class HOLOS_GlobalDebugMemTracer;

//

// #define HOLOS_DebugBasePrint    MGlobal->PRINT->setPrefix(__FILE__,__FUNCTION__,__LINE__);  MGlobal->PRINT->print
// #define HOLOS_DebugBaseDPrint   MGlobal->PRINT->clearPrefix();                              MGlobal->PRINT->print

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class HOLOS_GlobalDebugBase
{
    public:
        HOLOS_GlobalDebugBase(HOLOS_GlobalBase* AGlobal);
        ~HOLOS_GlobalDebugBase();
    public:
        HOLOS_GlobalBase*               getGlobal()     { return MGlobal; }
    public:
        HOLOS_GlobalDebugCallStack*     CALL_STACK      = nullptr;
        HOLOS_GlobalDebugCrashHandler*  CRASH_HANDLER   = nullptr;
        HOLOS_GlobalDebugMemTracer*     MEM_TRACER      = nullptr;
    protected:
        HOLOS_GlobalBase*               MGlobal         = nullptr;
};

//----------------------------------------------------------------------

HOLOS_GlobalDebugBase::HOLOS_GlobalDebugBase(HOLOS_GlobalBase* AGlobal)
{
    MGlobal = AGlobal;
}

HOLOS_GlobalDebugBase::~HOLOS_GlobalDebugBase()
{
}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------


//----------------------------------------------------------------------
#endif // holos_global_debug_base_included
