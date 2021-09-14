#ifndef MAIN_H
#define MAIN_H

#include "config.h"

struct RumbleData {
    u8 unk00; // comm
    u8 unk01; // level
    s16 unk02; // time
    s16 unk04; // decay
};

struct RumbleSettings {
    s16 unk00; // event
    s16 unk02; // level
    s16 unk04; // timer
    s16 unk06; // count
    s16 unk08; // start
    s16 unk0A; // slip
    s16 unk0C; // vibrate
    s16 unk0E; // decay
};

extern OSThread D_80339210;
extern OSThread gIdleThread;
extern OSThread gMainThread;
extern OSThread gGameLoopThread;
extern OSThread gSoundThread;
extern OSThread hvqmThread;
#if ENABLE_RUMBLE
extern OSThread gRumblePakThread;

extern OSPfs gRumblePakPfs;
#endif

extern OSMesgQueue gPIMesgQueue;
extern OSMesgQueue gIntrMesgQueue;
extern OSMesgQueue gSPTaskMesgQueue;
#if ENABLE_RUMBLE
extern OSMesgQueue gRumblePakSchedulerMesgQueue;
extern OSMesgQueue gRumbleThreadVIMesgQueue;
#endif
extern OSMesg gDmaMesgBuf[1];
extern OSMesg gPIMesgBuf[32];
extern OSMesg gSIEventMesgBuf[1];
extern OSMesg gIntrMesgBuf[16];
extern OSMesg gUnknownMesgBuf[16];
extern OSIoMesg gDmaIoMesg;
extern OSMesg gMainReceivedMesg;
extern OSMesgQueue gDmaMesgQueue;
extern OSMesgQueue gSIEventMesgQueue;
#if ENABLE_RUMBLE
extern OSMesg gRumblePakSchedulerMesgBuf[1];
extern OSMesg gRumbleThreadVIMesgBuf[1];

extern struct RumbleData gRumbleDataQueue[3];
extern struct RumbleSettings gCurrRumbleSettings;
#endif

extern struct VblankHandler *gVblankHandler1;
extern struct VblankHandler *gVblankHandler2;
extern struct SPTask *gActiveSPTask;
extern u32 gNumVblanks;
extern s8 gResetTimer;
extern s8 gNmiResetBarsTimer;
extern s8 gDebugLevelSelect;
extern s8 gShowProfiler;
extern s8 gShowDebugText;

void set_vblank_handler(s32 index, struct VblankHandler *handler, OSMesgQueue *queue, OSMesg *msg);
void dispatch_audio_sptask(struct SPTask *spTask);
void exec_display_list(struct SPTask *spTask);

#endif // MAIN_H
