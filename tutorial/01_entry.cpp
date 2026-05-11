/*

g++ 01_entry.cpp -o ../bin/01_entry.clap -I../src -std=gnu++17 -Wall -shared -fPIC

nc -U -l -k /tmp/debug_print.socket    

*/

//----------------------------------------------------------------------

#include <stdio.h>      // printf
#include <stdlib.h>     // malloc
#include <string.h>     // strcmp

#include "extern/clap/all.h"
#include "utils.h"

//----------------------------------------------------------------------
//
// entry
//
//----------------------------------------------------------------------

bool clap_entry_init_callback(const char *plugin_path)
{
    debug_print("clap_entry_init_callback : plugin_path: %s\n",plugin_path);
    return true;
}

//----------

void clap_entry_deinit_callback(void)
{
    debug_print("clap_entry_deinit_callback\n");
}

//----------

const void* clap_entry_get_factory_callback(const char* factory_id)
{
    debug_print("clap_entry_get_factory_callback : factory_id: %s\n",factory_id);
    if (strcmp(factory_id,CLAP_PLUGIN_FACTORY_ID) == 0)
    {
        debug_print("*** factory_id == CLAP_PLUGIN_FACTORY_ID >>> returning NULL\n");
        //return &my_clap_plugin_factory;
    }
    return nullptr;
}

//------------------------------
//
//------------------------------

CLAP_EXPORT extern const clap_plugin_entry_t clap_entry
{
    .clap_version   = CLAP_VERSION,
    .init           = clap_entry_init_callback,
    .deinit         = clap_entry_deinit_callback,
    .get_factory    = clap_entry_get_factory_callback
};
