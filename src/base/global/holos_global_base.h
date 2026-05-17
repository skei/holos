#ifndef holos_global_base_included
#define holos_global_base_included
//----------------------------------------------------------------------

class HOLOS_GlobalOS;
class HOLOS_GlobalPrint;
class HOLOS_GlobalDebug;
class HOLOS_GlobalLog;
class HOLOS_GlobalRegistry;

//----------

#define HOLOS_BasePrint    MGlobal->PRINT->setPrefix(__FILE__,__FUNCTION__,__LINE__);  MGlobal->PRINT->print
#define HOLOS_BaseDPrint   MGlobal->PRINT->clearPrefix();                              MGlobal->PRINT->print

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class HOLOS_GlobalBase
{
    public:
        HOLOS_GlobalBase();
        ~HOLOS_GlobalBase();
    public:
        HOLOS_GlobalOS*         OS          = nullptr;
        HOLOS_GlobalPrint*      PRINT       = nullptr;
        HOLOS_GlobalDebug*      DEBUG       = nullptr;
        HOLOS_GlobalLog*        LOG         = nullptr;
        HOLOS_GlobalRegistry*   REGISTRY    = nullptr;

    protected:

        // 'hack'
        // to make the HOLOS_BasePrint macro work everywhere MGlobal is available.. :-/
        HOLOS_GlobalBase*   MGlobal = this;
};

//----------------------------------------------------------------------

HOLOS_GlobalBase::HOLOS_GlobalBase()
{
}

HOLOS_GlobalBase::~HOLOS_GlobalBase()
{
}

//----------------------------------------------------------------------
#endif // holos_global_base_included
