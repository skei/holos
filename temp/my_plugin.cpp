
#include "extern/clap/all.h"

#include <stdio.h>      // printf
#include <stdlib.h>     // malloc
#include <string.h>     // strcmp

//----------------------------------------------------------------------
//
// clap plugin descriptor
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
// clap plugin
//
//----------------------------------------------------------------------

bool clap_plugin_init_callback(const struct clap_plugin *plugin)
{
    printf("clap_plugin_init_callback\n");
    return true;
}

void clap_plugin_destroy_callback(const struct clap_plugin *plugin)
{
    printf("clap_plugin_destroy_callback\n");
    // allocated in factory_create_plugin_callback()
    // // delele (Plugin*)plugin->plugin_data;
    free((void*)plugin);
}

bool clap_plugin_activate_callback(const struct clap_plugin *plugin, double sample_rate, uint32_t min_frames_count, uint32_t max_frames_count)
{
    printf("clap_plugin_activate_callback : sample_rate: %.2f min_frames: %i max_frames: %i\n",sample_rate,min_frames_count,max_frames_count);
    // Plugin* plug = (Plugin*)plugin->plugin_data;
    // plug->activate(sample_rate,min_frames_count,max_frames_count);
    return true;
}

void clap_plugin_deactivate_callback(const struct clap_plugin *plugin)
{
    printf("clap_plugin_deactivate_callback\n");
}

bool clap_plugin_start_processing_callback(const struct clap_plugin *plugin)
{
    printf("clap_plugin_start_processing_callback\n");
    return true;
}

void clap_plugin_stop_processing_callback(const struct clap_plugin *plugin)
{
    printf("clap_plugin_stop_processing_callback\n");
}

void clap_plugin_reset_callback(const struct clap_plugin *plugin)
{
    printf("clap_plugin_reset_callback\n");
}

clap_process_status clap_plugin_process_callback(const struct clap_plugin *plugin, const clap_process_t *process)
{
    //printf("clap_plugin_process_callback\n");
    return CLAP_PROCESS_CONTINUE;
}

const void* clap_plugin_get_extension_callback(const struct clap_plugin *plugin, const char *id)
{
    printf("clap_plugin_get_extension_callback : id: %s\n",id);
    return nullptr;
}

void clap_plugin_on_main_thread_callback(const struct clap_plugin *plugin)
{
    printf("clap_plugin_on_main_thread_callback\n");
}

//------------------------------
//
//------------------------------

clap_plugin_t my_clap_plugin = 
{
    .desc               = &my_clap_descriptor,
    .plugin_data        = nullptr,
    .init               = clap_plugin_init_callback,
    .destroy            = clap_plugin_destroy_callback,
    .activate           = clap_plugin_activate_callback,
    .deactivate         = clap_plugin_deactivate_callback,
    .start_processing   = clap_plugin_start_processing_callback,
    .stop_processing    = clap_plugin_stop_processing_callback,
    .reset              = clap_plugin_reset_callback,
    .process            = clap_plugin_process_callback,
    .get_extension      = clap_plugin_get_extension_callback,
    .on_main_thread     = clap_plugin_on_main_thread_callback
};

//----------------------------------------------------------------------
//
// clap plugin factory
//
//----------------------------------------------------------------------

uint32_t clap_plugin_factory_get_plugin_count_callback(const struct clap_plugin_factory *factory)
{
    printf("clap_plugin_factory_get_plugin_count_callback\n");
    return 1;
}

const clap_plugin_descriptor_t* clap_plugin_factory_get_plugin_descriptor_callback(const struct clap_plugin_factory *factory, uint32_t index)
{
    printf("clap_plugin_factory_get_plugin_descriptor_callback : index: %i\n",index);
    if (index == 0) return &my_clap_descriptor;
    return nullptr;
}

const clap_plugin_t* clap_plugin_factory_create_plugin_callback(const struct clap_plugin_factory *factory, const clap_host_t *host, const char *plugin_id)
{
    printf("clap_plugin_factory_create_plugin_callback : plugin_id: %s\n",plugin_id);
    if (strcmp(plugin_id,my_clap_descriptor.id) == 0)
    {
        // deleted in plugin_destroy_callback()
        clap_plugin_t* plugin = (clap_plugin_t*)malloc(sizeof(clap_plugin_t));
        if (plugin)
        {
            /*
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
            */
            memcpy(plugin,&my_clap_plugin,sizeof(clap_plugin_t));
            // plugin->desc                = &my_descriptor;
            // plugin->plugin_data         = nullptr;
            // // plugin->plugin_data         = new Plugin(host,plugin);
            return plugin;
        }
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
// clap entry
//
//----------------------------------------------------------------------

bool clap_entry_init_callback(const char *plugin_path)
{
    printf("clap_enry_init_callback : plugin_path: %s\n",plugin_path);
    return true;
}

void clap_entry_deinit_callback(void)
{
    printf("clap_entry_deinit_callback\n");
}

const void* clap_entry_get_factory_callback(const char* factory_id)
{
    printf("clap_entry_get_factory_callback : factory_id: %s\n",factory_id);
    if (strcmp(factory_id,CLAP_PLUGIN_FACTORY_ID) == 0) return &my_clap_plugin_factory;
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
