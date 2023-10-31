#include "seq_ids.h"
#include "audio/external.h"
#include "audio/load.h"
#include "audio/synthesis.h"

struct PhonographStream {
    u8 seqId;
    u8 bankId;         // Somewhat hacky, but easier to check just bank than both bank and instrument ID. Assumes all supported streamed tracks possess their own sound bank, or at least aren't playing more than one at a time.
    f32 tempo;
    s32 sampleRate;
    s32 sampleOffset;  // Audio samples from the beginning to offset the phono player animations, in case audio file contains silence at the beginning or if there's audio-video desync
    s32 numberOfBeats; // Negative value if looping
};

// NOTE: This assumes anything streamed is properly grid-locked to tempo and includes no sorts of tempo changes
struct PhonographStream streamedParams[] = {
    {
        .seqId         = 0,//SEQ_STREAMED_BAD_APPLE,
        .bankId        = 0x2D,
        .tempo         = 138.0f,
        .sampleRate    = 32000, 
        .sampleOffset  = 600,
        .numberOfBeats = 496,
    },
};

void bhv_phono_init(void) {
    o->oPhonographScale = 0.0f;
}

void phono_update_normal(void) {
    cur_obj_scale(o->oPhonographScale + 1.0f);

    o->oPhonographScale *= 0.95f;
    
    if (global_audio_hit) {
        global_audio_hit = FALSE;
        o->oPhonographScale = 0.5f;
    }
    
    o->oPhonographScaleLast = o->oPhonographScale;
}

void phono_update_by_sample_pos(s32 samplePos, struct PhonographStream *stream) {
    f64 samplesPerBeat = (stream->sampleRate * 60) / (f64) stream->tempo; // f64 potentially warranted here for precision

    s32 offset = samplePos - stream->sampleOffset;
    if (offset < 0) {
        global_audio_hit = FALSE;
        phono_update_normal();
        return;
    }

    // Calculate beat position in track
    f32 absolutePosition = (f32) (offset / samplesPerBeat);
    if (stream->numberOfBeats > 0 && (s32) absolutePosition >= stream->numberOfBeats) {
        // Song is over, default to standard behavior
        phono_update_normal();
        return;
    }
    f32 relativePosition = absolutePosition - (s32) absolutePosition; // Final value should always be in a [0, 1) range

    // Compute phonograph size
    u16 posInt = relativePosition * 65536.0f;
    posInt += 0xC000;
    if (posInt < 0xC000) {
        posInt = (u32) posInt * 2 / 3; // Convert to [0x0000, 0x8000)
    } else {
        posInt *= 2; // Convert to [0x8000, 0x10000)
    }

    f32 sizeMult = (coss(posInt) + 1.0f) * 0.5f;
    if (posInt >= 0x8000) {
        sizeMult *= sizeMult * sizeMult;
    }

    // Phonograph scale bounds
    if (absolutePosition < 0.25f) { // posInt starts at 0xC000, peak at 0x0000 (overflow); that's 0.25 of a full cycle.
        // First cycle should go off of the previous phonograph state
        sizeMult = (sizeMult * (0.5f - o->oPhonographScaleLast)) + o->oPhonographScaleLast;
    } else {
        // Future cycles should be bounded to a constant, equivalent to the function of the above but forced to 0.167f
        sizeMult = (sizeMult * 0.333f) + 0.167f;
    }

    // Set the final size values
    o->oPhonographScale = sizeMult;
    cur_obj_scale(o->oPhonographScale + 1.0f);
}

// Hardcoded case to handle streamed audio
void phono_update_streamed_track(s32 seqId) {
    struct Note *note;
    struct PhonographStream *stream = NULL;

    // Get the matching streamed track we want to use
    for (s32 i = 0; i < ARRAY_COUNT(streamedParams); i++) {
        if (seqId == streamedParams[i].seqId) {
            stream = &streamedParams[i];
            break;
        }
    }

    if (!stream) {
        // Streamed track updates are being called by mistake! Really this should be using an assertion but idk if those are set up properly in this repo.
        phono_update_normal();
        return;
    }

    // Check against active note list to see if any streamed notes match
    for (s32 noteIndex = 0; noteIndex < gMaxSimultaneousNotes; noteIndex++) {
        note = &gNotes[noteIndex];

        if (((struct vNote *) note)->enabled && note->needsInit == FALSE && note->bankId == stream->bankId) {
            phono_update_by_sample_pos(note->samplePosInt, stream);
            return;
        }
    }

    // Fallthrough to safeguard case if no bank match is found
    phono_update_normal();
}

void bhv_phono_loop(void) {
    s32 seqId = (u8) get_current_background_music();
    switch (seqId) {
        //case SEQ_STREAMED_BAD_APPLE:
            //phono_update_streamed_track(seqId);
            //global_audio_hit = FALSE;
            //break;
        default:
            phono_update_normal();
            break;
    }
}
