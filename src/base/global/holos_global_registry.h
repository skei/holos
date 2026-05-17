#ifndef holos_global_registry_included
#define holos_global_registry_included
//----------------------------------------------------------------------

#include "base/global/holos_global_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class HOLOS_GlobalRegistry
{
    friend class HOLOS_Global;
    public:
        HOLOS_GlobalRegistry(HOLOS_GlobalBase* AGlobal);
        ~HOLOS_GlobalRegistry();
    private:
        void        initialize();
        void        cleanup();
    private:
        HOLOS_GlobalBase*   MGlobal = nullptr;
};

//----------------------------------------------------------------------

HOLOS_GlobalRegistry::HOLOS_GlobalRegistry(HOLOS_GlobalBase* AGlobal)
{
    MGlobal = AGlobal;
}

HOLOS_GlobalRegistry::~HOLOS_GlobalRegistry()
{
}

//------------------------------
//
//------------------------------

void HOLOS_GlobalRegistry::initialize()
{
    HOLOS_BasePrint("\n");
}

void HOLOS_GlobalRegistry::cleanup()
{
    HOLOS_BasePrint("\n");
}

//----------------------------------------------------------------------
#endif // holos_global_registry_included
