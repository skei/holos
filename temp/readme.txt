
.clap
    compile (.so)
        -shared, -fPIC
    clap_entry
    plugin factory
    descriptor
        .id
        .features

clap_plugin_t
    .plugin_data
    callbacks
        init, deinit
        activate, deactivate
        start, stop processing
        get_extension
        process

extensions
    ext: audio-ports

process
    frames_count
    clap_audio_buffer_t
    clap_input_events_t
    clap_output_events_t
    events
        type
            notes, params, transport, midi
        space_id
            CLAP_CORE_EVENT_SPACE_ID
            (ext: event-registry)
        flags
            is_live, dont_record
        time
            (sorted)
        pckn: port, channel, key, (note_id)
    return clap_process_status

-----

audio effect
    CLAP_PLUGIN_FEATURE_AUDIO_EFFECT

instrument
    CLAP_PLUGIN_FEATURE_INSTRUMENT
    ext: note-ports
    ext: voice-info
    note events
        pck/note_id
        - note on
        - note off
        - note expression
        * note end

note effect
    CLAP_PLUGIN_FEATURE_NOTE_EFFECT

-----

parameters
    ext: params
        param_info
            id
            flags
            cookie
        ev: param value
        ev: param mod
    (ext: state)
    (? init)
    (? presets)

gui
    ev: param value -> host
    param gesture begin/end -> host
    (-> gui)
    param-indication
    (timer-support)

----------------------------------------------------------------------
notes
----------------------------------------------------------------------

events

    host->plugin
    plugin->host
        note_end
    plugin->host->next_plugin
        ? note_expression

event queue
    pointers const/valid for entire audio block

