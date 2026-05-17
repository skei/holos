#ifndef holos_global_print_included
#define holos_global_print_included
//----------------------------------------------------------------------

/*
    todo:
    - bool flags instead of #defines, so we can change at runtime
    - enableTime, enableThread
    - setPrefix, setColoredPrefix
    - printStdout, printSocket, printFile
*/

//----------------------------------------------------------------------

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

//----------

#ifdef HOLOS_PRINT_SOCKET
    #if defined HOLOS_LINUX
        #include <sys/socket.h> // socket, connect
        #include <sys/un.h>     // sockaddr_un
        #include <unistd.h>     // close
    #elif defined HOLOS_WIN32
        // #ifndef _WIN32_WINNT
        //     #define _WIN32_WINNT 0x0600
        // #endif
        // #include <winsock2.h>
        // #include <ws2tcpip.h>
    #else
        #error not implemented
    #endif
#endif

#ifdef HOLOS_PRINT_TIME
    #include <sys/time.h> // gettimeofday
#endif

#ifdef HOLOS_PRINT_THREAD
    #if defined HOLOS_LINUX
        #include <sys/syscall.h>
        #include <sys/unistd.h>
        #define gettid() syscall(SYS_gettid)
    #elif defined HOLOS_WIN32
        // #include <processthreadsapi.h>
    #else
        #error not implemented
    #endif
#endif

//----------

#include "base/global/holos_global_base.h"

//------------------------------
//
//------------------------------

//#define HOLOS_PRINT_SOCKET

#ifndef HOLOS_PRINT_SOCKET_NAME
    #define HOLOS_PRINT_SOCKET_NAME "/tmp/holos.print"
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class HOLOS_GlobalPrint
{
    friend class HOLOS_Global;
    public:
        HOLOS_GlobalPrint(HOLOS_GlobalBase* AGlobal);
        ~HOLOS_GlobalPrint();
    public:
        void        setPrefix(const char* file, const char* func, uint32_t line);
        void        clearPrefix();
        void        print(const char* format, ...);
    private:
        void        initialize();
        void        cleanup();
        bool        socketSetup();
        void        socketCleanup();
        bool        timeStart();
        double      timeElapsed();
        const char* stripPath(const char* buffer);
    private:
        HOLOS_GlobalBase*   MGlobal             = nullptr;
        char                MPrintBuffer[1024]  = {0};
        char                MPrefixBuffer[1024] = {0};
        #ifdef HOLOS_PRINT_SOCKET
            #if defined HOLOS_LINUX
                int         MSocketHandle       = 0;
            #elif defined HOLOS_WIN32
                SOCKET      MSocketHandle       = 0;
                WSADATA     MWsadata            = {};
            #else
                #error not implemented
            #endif
        #endif
        #ifdef HOLOS_PRINT_TIME
            double          MStartTime          = 0.0;
        #endif
};

//----------------------------------------------------------------------

HOLOS_GlobalPrint::HOLOS_GlobalPrint(HOLOS_GlobalBase* AGlobal)
{
    MGlobal = AGlobal;
}

HOLOS_GlobalPrint::~HOLOS_GlobalPrint()
{
}

//------------------------------
//
//------------------------------

void HOLOS_GlobalPrint::initialize()
{
    socketSetup();
    timeStart();
    {
        setPrefix(__FILE__,__FUNCTION__,__LINE__);
        print("\n");
    }
}

void HOLOS_GlobalPrint::cleanup()
{
    {
        setPrefix(__FILE__,__FUNCTION__,__LINE__);
        print("\n");
    }
    socketCleanup();
}

//------------------------------
// socket
//------------------------------

// nc -U -l -k /tmp/holos.socket

bool HOLOS_GlobalPrint::socketSetup()
{
    #ifdef HOLOS_PRINT_SOCKET
        MSocketHandle = socket(PF_UNIX,SOCK_STREAM,0);
        sockaddr_un address;
        memset(&address,0,sizeof(sockaddr_un));
        address.sun_family = AF_UNIX;
        snprintf(address.sun_path,108,HOLOS_PRINT_SOCKET_NAME); // max 108?
        connect(MSocketHandle,reinterpret_cast<sockaddr*>(&address),sizeof(sockaddr_un));
    #endif
    return true;
}

void HOLOS_GlobalPrint::socketCleanup()
{
    #ifdef HOLOS_PRINT_SOCKET
        close(MSocketHandle);
    #endif
}

//------------------------------
// time
//------------------------------

bool HOLOS_GlobalPrint::timeStart()
{
    #ifdef HOLOS_PRINT_TIME
        struct timeval time;
        gettimeofday(&time,NULL);
        MStartTime = (double)time.tv_sec + (double)time.tv_usec * .000001;
    #endif
    return true;
}

double HOLOS_GlobalPrint::timeElapsed()
{
    double elapsed = 0.0;
    #ifdef HOLOS_PRINT_TIME
        struct timeval time;
        gettimeofday(&time,NULL);
        double currenttime = (double)time.tv_sec + (double)time.tv_usec * .000001;
        elapsed = currenttime - MStartTime;
    #endif
    return elapsed;
}

//------------------------------
// path
//------------------------------

const char* HOLOS_GlobalPrint::stripPath(const char* buffer)
{
    const char *slash;
    slash = strrchr(buffer,'/');
    if (slash)
    {
        return slash + 1;
    }
    return buffer;
}

//------------------------------
// print
//------------------------------

void HOLOS_GlobalPrint::setPrefix(const char* file, const char* func, uint32_t line)
{
    #ifdef HOLOS_PRINT_COLORS
        sprintf(MPrefixBuffer,
            "["
            
                // file
                HOLOS_TERM_FG_GREEN "%s" HOLOS_TERM_RESET

                // line
                ":" HOLOS_TERM_FG_RED "%i" HOLOS_TERM_RESET

                // func
                ":" HOLOS_TERM_FG_YELLOW "%s" HOLOS_TERM_RESET

                // time
                #ifdef HOLOS_PRINT_TIME
                    ":" HOLOS_TERM_FG_MAGENTA "%.6f" HOLOS_TERM_RESET
                #endif

                // thread id
                #ifdef HOLOS_PRINT_THREAD
                    ":" HOLOS_TERM_FG_CYAN "%08x" HOLOS_TERM_RESET
                #endif

            "]",
            stripPath(file), line, func

            #ifdef HOLOS_PRINT_TIME
                , timeElapsed()
            #endif

            #if defined HOLOS_PRINT_THREAD
                #if defined HOLOS_LINUX
                    , (uint32_t)gettid()
                #elif defined SAT_WIN32
                    , (uint32_t)GetCurrentThreadId()
                #else
                    #error not implemented
                #endif
            #endif

        );

    #else // !HOLOS_PRINT_COLORS

        sprintf(MPrefixBuffer,
            "["

                // file, line, func
                "%s:%i:%s"

                // time
                #ifdef HOLOS_PRINT_TIME
                    ":%.6f"
                #endif

                // thread id
                #ifdef HOLOS_PRINT_THREAD
                    ":%08x"
                #endif

            "] ",
            stripPath(file), line, func

            #ifdef HOLOS_PRINT_TIME
                , timeElapsed()
            #endif

            #if defined HOLOS_PRINT_THREAD
                #if defined HOLOS_LINUX
                    , (uint32_t)gettid()
                #elif defined SAT_WIN32
                    , (uint32_t)GetCurrentThreadId()
                #else
                    #error not implemented
                #endif
            #endif

        );

    #endif // HOLOS_PRINT_SOCKET
}

void HOLOS_GlobalPrint::clearPrefix()
{
    MPrefixBuffer[0] = 0;
}

void HOLOS_GlobalPrint::print(const char* format, ...)
{
    va_list args;
    va_start(args,format);
    vsprintf(MPrintBuffer,format,args);
    va_end(args);
    #ifdef HOLOS_PRINT_SOCKET
        dprintf(MSocketHandle,"%s %s",MPrefixBuffer,MPrintBuffer);
    #else
        printf("%s%s",MPrefixBuffer,MPrintBuffer);
    #endif
}


//----------------------------------------------------------------------
#endif // holos_global_print_included










#if 0





//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

HOLOS_GlobalPrint holos_global_print = {};

//----------

#define HOLOS_Print     holos_global_print.setPrefix(__FILE__,__FUNCTION__,__LINE__); holos_global_print.print
#define HOLOS_DPrint    holos_global_print.clearPrefix(); holos_global_print.print

#endif // 0

