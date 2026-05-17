#ifndef holos_included
#define holos_included
//----------------------------------------------------------------------

#include "base/holos_base.h"
#include "base/holos_global.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

// DANGER! Global variable!
HOLOS_Global HOLOS = {};

//------------------------------
//
//------------------------------

#define HOLOS_Print     HOLOS.PRINT->setPrefix(__FILE__,__FUNCTION__,__LINE__); HOLOS.PRINT->print
#define HOLOS_DPrint    HOLOS.PRINT->clearPrefix();                             HOLOS.PRINT->print

//----------------------------------------------------------------------
#endif // holos_included
