// nc -U -l -k /tmp/debug_print.socket

#include <sys/socket.h>     // socket, connect
#include <sys/un.h>         // sockaddr_un
#include <unistd.h>         // close
#include <stdio.h>          // snprintf

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class socket_print
{
    public:

        socket_print()
        {
            socket_handle = socket(PF_UNIX,SOCK_STREAM,0);
            sockaddr_un address;
            memset(&address,0,sizeof(sockaddr_un));
            address.sun_family = AF_UNIX;
            snprintf(address.sun_path,108,"/tmp/debug_print.socket"); // max 108?
            connect(socket_handle,reinterpret_cast<sockaddr*>(&address),sizeof(sockaddr_un));    
        }

        ~socket_print()
        {
            close(socket_handle);    
        }

    public:

        int socket_handle = 0;
};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

socket_print global_debug_print = {};

#define debug_print(...) dprintf(global_debug_print.socket_handle,__VA_ARGS__)
