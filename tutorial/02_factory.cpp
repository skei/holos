/*

g++ 02_factory.cpp -o ../bin/02_factory.clap -I../src -std=gnu++17 -Wall -shared -fPIC

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
// descriptor
//
//----------------------------------------------------------------------

const clap_plugin_descriptor_t my_clap_descriptor =
{
    .clap_version   = CLAP_VERSION,
    .id             = "me/my_clap_plugin",
    .name           = "my_clap_plugin",
    .vendor         = "me",
    .url            = "https://my_website.com/my_clap_plugin",
    .manual_url     = "https://my_website.com/my_clap_plugin/manual.pdf",
    .support_url    = "https://my_website.com/support",
    .version        = "0.0.0",
    .description    = "my_clap_plugin description here",
    .features       = (const char*[])
    {
        CLAP_PLUGIN_FEATURE_AUDIO_EFFECT,
        nullptr
    }
};

//----------------------------------------------------------------------
//
// factory
//
//----------------------------------------------------------------------

uint32_t clap_plugin_factory_get_plugin_count_callback(const struct clap_plugin_factory *factory)
{
    debug_print("clap_plugin_factory_get_plugin_count_callback\n");
    return 1;
}

//----------

const clap_plugin_descriptor_t* clap_plugin_factory_get_plugin_descriptor_callback(const struct clap_plugin_factory *factory, uint32_t index)
{
    debug_print("clap_plugin_factory_get_plugin_descriptor_callback : index: %i\n",index);
    if (index == 0)
    {
        debug_print("*** index == 0 >>> returning my_clap_descriptor\n");
        return &my_clap_descriptor;
    }
    return nullptr;
}

//----------

const clap_plugin_t* clap_plugin_factory_create_plugin_callback(const struct clap_plugin_factory *factory, const clap_host_t *host, const char *plugin_id)
{
    debug_print("clap_plugin_factory_create_plugin_callback : plugin_id: %s\n",plugin_id);
    if (strcmp(plugin_id,my_clap_descriptor.id) == 0)
    {
        debug_print("*** plugin_id == my_clap_descriptor.id >>> returning NULL\n");
        /*
        size_t size = sizeof(clap_plugin_t);
        // deleted in plugin_destroy_callback()
        clap_plugin_t* plugin = (clap_plugin_t*)malloc(size);
        if (plugin)
        {
            plugin->desc                = &my_descriptor;
            plugin->plugin_data         = nullptr; // instance-specific data
            plugin->init                = plugin_init_callback;
            plugin->destroy             = plugin_destroy_callback;
            plugin->activate            = plugin_activate_callback;
            plugin->deactivate          = plugin_deactivate_callback;
            plugin->start_processing    = plugin_start_processing_callback;
            plugin->stop_processing     = plugin_stop_processing_callback;
            plugin->reset               = plugin_reset_callback;
            plugin->process             = plugin_process_callback;
            plugin->get_extension       = plugin_get_extension_callback;
            plugin->on_main_thread      = plugin_on_main_thread_callback;
            return plugin;
        }
        */
    }
    return nullptr;
}

//------------------------------
//
//------------------------------

const clap_plugin_factory_t my_clap_plugin_factory
{
    .get_plugin_count       = clap_plugin_factory_get_plugin_count_callback,
    .get_plugin_descriptor  = clap_plugin_factory_get_plugin_descriptor_callback,
    .create_plugin          = clap_plugin_factory_create_plugin_callback
};

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
        debug_print("*** factory_id == CLAP_PLUGIN_FACTORY_ID >>> returning my_clap_plugin_factory\n");
        return &my_clap_plugin_factory;

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
