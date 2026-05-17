#ifndef holos_global_included
#define holos_global_included
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdarg.h>

#include "base/global/holos_global_base.h"

#include "base/global/holos_global_print.h"
#include "base/global/holos_global_os.h"
#include "base/global/holos_global_debug.h"
#include "base/global/holos_global_log.h"
#include "base/global/holos_global_registry.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class HOLOS_Global
: public HOLOS_GlobalBase
{
    public:
        HOLOS_Global();
        ~HOLOS_Global();
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

HOLOS_Global::HOLOS_Global()
: HOLOS_GlobalBase()
{
    OS          = new HOLOS_GlobalOS(this);
    PRINT       = new HOLOS_GlobalPrint(this);
    DEBUG       = new HOLOS_GlobalDebug(this);
    LOG         = new HOLOS_GlobalLog(this);
    REGISTRY    = new HOLOS_GlobalRegistry(this);
    initialize();
}

HOLOS_Global::~HOLOS_Global()
{
    cleanup();
    if (REGISTRY)   delete REGISTRY;
    if (LOG)        delete LOG;
    if (DEBUG)      delete DEBUG;
    if (PRINT)      delete PRINT;
    if (OS)         delete OS;
}

//------------------------------
//
//------------------------------

void HOLOS_Global::initialize()
{
    HOLOS_BasePrint("\n");
    if (!MInitialized)
    {
        OS->initialize();
        PRINT->initialize();
        DEBUG->initialize();
        LOG->initialize();
        REGISTRY->initialize();
        MInitialized = true;
    }
}

void HOLOS_Global::cleanup()
{
    HOLOS_BasePrint("\n");
    if (MInitialized)
    {
        if (REGISTRY)   REGISTRY->cleanup();
        if (LOG)        LOG->cleanup();
        if (DEBUG)      DEBUG->cleanup();
        if (PRINT)      PRINT->cleanup();
        if (OS)         OS->cleanup();
        MInitialized = false;
    }
}

//----------------------------------------------------------------------
#endif // holos_global_included
