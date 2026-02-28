#ifndef holos_core_included
#define holos_core_included
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//
// declaration
//
//----------------------------------------------------------------------

bool holos_init();
bool holos_exit();

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

#ifdef INCLUDE_HOLOS_CORE_IMPLEMENTATION

bool holos_init()
{
    return true;
}

bool holos_exit()
{
    return true;
}

#endif INCLUDE_HOLOS_CORE_IMPLEMENTATION

//----------------------------------------------------------------------
#endif
