#ifndef holos_global_debug_mem_trace_included
#define holos_global_debug_mem_trace_included
//----------------------------------------------------------------------

#include <stdint.h>
//#include <stdio.h>
#include <stdlib.h>
//#include <memory.h>

#include <new>

//----------

#include "base/global/debug/holos_global_debug_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class HOLOS_GlobalDebugMemTracer
{
    friend class HOLOS_GlobalDebug;
    public:
        HOLOS_GlobalDebugMemTracer(HOLOS_GlobalDebugBase* AGlobalDebug);
        ~HOLOS_GlobalDebugMemTracer();
    public:
        // void*   _malloc(size_t size, const char* file, uint32_t line);
        // void*   _calloc(size_t size, const char* file, uint32_t line);
        // void*   _realloc(size_t size, const char* file, uint32_t line);
        // void    _free(void* ptr, const char* file, uint32_t line);
        // void*   _new(size_t size, const char* file, uint32_t line);
        // void    _delete(void* ptr, const char* file, uint32_t line);
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

HOLOS_GlobalDebugMemTracer::HOLOS_GlobalDebugMemTracer(HOLOS_GlobalDebugBase* AGlobalDebug)
{
    MGlobalDebug = AGlobalDebug;
    MGlobal = MGlobalDebug->getGlobal();
}

HOLOS_GlobalDebugMemTracer::~HOLOS_GlobalDebugMemTracer()
{
}

//------------------------------
//
//------------------------------

void HOLOS_GlobalDebugMemTracer::initialize()
{
    HOLOS_BasePrint("\n");
}

void HOLOS_GlobalDebugMemTracer::cleanup()
{
    HOLOS_BasePrint("\n");
}

//------------------------------
//
//------------------------------

//----------------------------------------------------------------------
#endif // holos_global_debug_mem_trace_included















#if 0

void* HOLOS_MemTrace::_malloc(size_t size, const char* file, uint32_t line)
{
    HOLOS_Print("\n");
    return malloc(size);
}

void HOLOS_MemTrace::_free(void* ptr, const char* file, uint32_t line)
{
    HOLOS_Print("\n");
    free(ptr);
}

void* HOLOS_MemTrace::_new(size_t size, const char* file, uint32_t line)
{
    HOLOS_Print("size: %i file: %s line: %i\n",size,file,line);
    return malloc(size);
}

void HOLOS_MemTrace::_delete(void* ptr, const char* file, uint32_t line)
{
    HOLOS_Print("ptr: %p file: %s line: %i\n",ptr,file,line);
    free(ptr);
}

#endif // 0

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#if 0

HOLOS_MemTrace  holos_global_memtrace = {};

//----------

#define malloc(size)    holos_global_memtrace._malloc(size, __FILE__, __LINE__)
#define free(ptr)       holos_global_memtrace._free(ptr, __FILE__, __LINE__)

//#define calloc(n,s)     holos_global_memtrace.memCAlloc(    n, s,   0,  __FILE__, __LINE__ )
//#define realloc(p,s)    holos_global_memtrace.memreAlloc(   p, s,   0,  __FILE__, __LINE__ )

void* operator  new     (const size_t size, const char* file, unsigned int line)    { return holos_global_memtrace._new(size, file, line); }
void  operator  delete  (void* ptr, const char* file, unsigned int line)            { return holos_global_memtrace._delete(ptr, file, line); }

// inline __attribute__((always_inline)) void my_function() {
//     // Code to be inlined
// }

//----------

#define new     new(__FILE__, __LINE__)
#define delete  delete(__FILE__, __LINE__)

#endif // 0






















//----------------------------------------------------------------------

#if 0

    void* operator  new         (const size_t size, const char* file, unsigned int line)    { return SAT.DEBUG->MEMTRACE->malloc(size, file, line, 1); }
    void* operator  new[]       (const size_t size, const char* file, unsigned int line)    { return SAT.DEBUG->MEMTRACE->malloc(size, file, line, 1); }

    void  operator  delete      (void* ptr)                                                 { return SAT.DEBUG->MEMTRACE->free(ptr, sat_memtrace_prefix_file, sat_memtrace_prefix_line, 1); }
    void  operator  delete[]    (void* ptr)                                                 { return SAT.DEBUG->MEMTRACE->free(ptr, sat_memtrace_prefix_file, sat_memtrace_prefix_line, 1); }

    #define new     new(__FILE__, __LINE__)
    #define delete  if (sat_memtrace_prefix(__FILE__, __LINE__)) delete

    #define malloc(s)       SAT.DEBUG->MEMTRACE->malloc(  s,    __FILE__, __LINE__ )
    #define calloc(n,s)     SAT.DEBUG->MEMTRACE->calloc(  n, s, __FILE__, __LINE__ )
    #define realloc(p,s)    SAT.DEBUG->MEMTRACE->realloc( p, s, __FILE__, __LINE__ )
    #define free(p)         SAT.DEBUG->MEMTRACE->free(    p,    __FILE__, __LINE__ )

#endif // 0

//----------------------------------------------------------------------

#if 0

//

#if defined _MSC_VER || defined _WIN32 || defined __ANDROID__ || defined MUSL || defined DISABLE_BACKTRACE

    // TODO: backtrace() is not supported on Windows and Android.
    // On Windows we can use dbghelp but it's not supported on MinGW. Need to figure out a way to solve it on all platforms

    const char* getCaller()
    {
        return "Unknown";
    }

#elif defined(__has_include) && __has_include(<execinfo.h>)

    // Check if execinfo.h is available (glibc systems)
    #include <execinfo.h>

    const char* getCaller()
    {
        void* backtraceArr[3];
        size_t backtraceArrSize;
        // get void*'s for all entries on the stack
        backtraceArrSize = backtrace(backtraceArr, 3);
        if (backtraceArrSize < 3)
        {
            return "Unknown";
        }
        // get the symbols
        char** backtraceSymbols = backtrace_symbols(backtraceArr, backtraceArrSize);
        // the caller is second in the backtrace
        return backtraceSymbols[2];
    }

#else

    // Systems without execinfo.h (e.g., Alpine Linux with musl libc)
    const char* getCaller()
    {
        return "Unknown";
    }

#endif

//------------------------------
// new
//------------------------------

void* operator new(std::size_t size, const char* file, int line)
{
    return MemPlumberInternal::getInstance().allocateMemory(size, file, line);
}

//

void* operator new(size_t size) _THROW_BAD_ALLOC
{
    return operator new(size, getCaller(), 0);
}

void* operator new(size_t size, const std::nothrow_t&) _NOEXCEPT
{
    return operator new(size, getCaller(), 0);
}

//------------------------------
// new []
//------------------------------

void* operator new[](std::size_t size, const char* file, int line)
{
    return operator new(size, file, line);
}

//

void* operator new[](size_t size) _THROW_BAD_ALLOC
{
    return operator new(size, getCaller(), 0);
}

void* operator new[](size_t size, const std::nothrow_t&) _NOEXCEPT
{
    return operator new[](size, getCaller(), 0);
}

//------------------------------
// delete
//------------------------------

void operator delete(void* pointer, const char* file, int line)
{
    MemPlumberInternal::getInstance().freeMemory(pointer, file, line);
}

//

void operator delete(void* pointer) throw()
{
    operator delete(pointer, __FILE__, __LINE__);
}

void operator delete(void* pointer, std::size_t size)
{
    operator delete(pointer, __FILE__, __LINE__);
}

void operator delete(void* pointer, const std::nothrow_t&) throw()
{
    operator delete(pointer);
}

//------------------------------
// delete []
//------------------------------

void operator delete[](void* pointer, const char* file, int line)
{
    operator delete(pointer, file, line);
}

//

void operator delete[](void* pointer) _NOEXCEPT
{
    operator delete(pointer, __FILE__, __LINE__);
}

void operator delete[](void* pointer, std::size_t size)
{
    operator delete(pointer, __FILE__, __LINE__);
}

void operator delete[](void* pointer, const std::nothrow_t&) throw()
{
    operator delete(pointer, std::nothrow);
}

#endif // 0
