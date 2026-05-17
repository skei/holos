// compile -i build.cpp -o ../bin/buid.exe -f exe
// nc -U -l -k /tmp/holos.socket

#include "holos.h"

int main()
{
    HOLOS_DPrint("\n");
    HOLOS_Print("hello world!\n");
    HOLOS_DPrint("hello world!\n");
    HOLOS_DPrint("\n");
    return 0;
}

















//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#if 0

#include "holos.h"
#include "plugin/holos_plugin.h"
#include "plugin/holos_entry.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

const clap_plugin_descriptor_t myDescriptor =
{
    .clap_version = CLAP_VERSION,
    .id           = "me/my_plugin",
    .name         = "my_plugin",
    .vendor       = "me",
    .url          = "https://my_website.com/my_plugin",
    .manual_url   = "https://my_website.com/my_plugin/manual.pdf",
    .support_url  = "https://my_website.com/support",
    .version      = "0.0.0",
    .description  = "my_plugin description here..",
    .features     = (const char* [])
    {
        CLAP_PLUGIN_FEATURE_AUDIO_EFFECT,
        nullptr
    }
};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class myPlugin
: public HOLOS_Plugin
{
    public:
        myPlugin(const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost);
        virtual ~myPlugin();
    private:
};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

myPlugin::myPlugin(const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost)
: HOLOS_Plugin(ADescriptor,AHost)
{
}

myPlugin::~myPlugin()
{
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

// int main()
// {
//     return 0;
// }

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

bool HOLOS_ClapInit(const char *plugin_path)
{
    printf("HOLOS_ClapInit\n");
    return true;
}

void HOLOS_ClapDeinit()
{
    printf("HOLOS_ClapDeinit\n");
}

//------------------------------
//
//------------------------------

const clap_plugin_descriptor_t* HOLOS_GetDescriptor(uint32_t index)
{
    printf("HOLOS_GetDescriptor\n");
    if (index == 0) return &myDescriptor;
    return nullptr;
}

HOLOS_Plugin* HOLOS_CreatePlugin(const clap_host_t *host, const char *plugin_id)
{
    printf("HOLOS_CreatePlugin\n");
    if (strcmp(plugin_id,myDescriptor.id) == 0)
    {
        HOLOS_Plugin* plugin = new HOLOS_Plugin(&myDescriptor,host);
        return plugin;
    }
    return nullptr;
}

#endif // 0
