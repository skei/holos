#ifndef holos_global_log_included
#define holos_global_log_included
//----------------------------------------------------------------------

#include "base/global/holos_global_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class HOLOS_GlobalLog
{
    friend class HOLOS_Global;
    public:
        HOLOS_GlobalLog(HOLOS_GlobalBase* AGlobal);
        ~HOLOS_GlobalLog();
    private:
        void        initialize();
        void        cleanup();
    private:
        HOLOS_GlobalBase*   MGlobal = nullptr;
};

//----------------------------------------------------------------------

HOLOS_GlobalLog::HOLOS_GlobalLog(HOLOS_GlobalBase* AGlobal)
{
    MGlobal = AGlobal;
}

HOLOS_GlobalLog::~HOLOS_GlobalLog()
{
}

//------------------------------
//
//------------------------------

void HOLOS_GlobalLog::initialize()
{
    HOLOS_BasePrint("\n");
}

void HOLOS_GlobalLog::cleanup()
{
    HOLOS_BasePrint("\n");
}

//----------------------------------------------------------------------
#endif // holos_global_log_included
