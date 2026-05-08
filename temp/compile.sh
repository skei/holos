
g++                         \
    my_plugin.cpp           \
    -o my_plugin.clap       \
    -I../src                \
                            \
    -std=gnu++17            \
    -Wall                   \
    -fno-exceptions         \
    -pthread                \
                            \
    -shared                 \
    -fPIC                   \
                            \
    -g                      \
    -rdynamic

#------------------------------
#
#   -o                  name and location of the output file
#   -I                  include directory
#
#   -std=gnu++17        use C++17 standard, enable GNU-specific extensions
#   -Wall               enable a broad set of compiler warnings (not actually all, see also -Wextra, -Werror, -Wpedantic)
#   -fno-exceptions     disable C++ exception handling
#   -pthread            enable support for multithreading using POSIX threads
#
#   -shared             produce a shared object (.so) instead of a standard executable
#   -fPIC               Position Independent Code, needed for .so
#
#   -g                  generate debugging information
#   -rdynamic           export all symbols
#
#-----
#
#   -Wl,--as-needed     only link shared libraries if the binary actually uses symbols from them
#   -lm                 link standard math library
#   -lrt                link Realtime Extensions library (timers, shared memory, ..())
#   -ldl                link libdl (to manually load other shared libraries)

