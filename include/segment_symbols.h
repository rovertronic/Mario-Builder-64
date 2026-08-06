#ifndef SEGMENT_SYMBOLS_H
#define SEGMENT_SYMBOLS_H

#ifndef NO_SEGMENTED_MEMORY
#define DECLARE_SEGMENT(name) \
    extern u8 _##name##SegmentRomStart[]; \
    extern u8 _##name##SegmentRomEnd[];

#define DECLARE_NOLOAD(name) \
    extern u8 _##name##SegmentBssStart[]; \
    extern u8 _##name##SegmentBssEnd[];

#define DECLARE_ACTOR_SEGMENT(name) \
    DECLARE_SEGMENT(name##_mio0) \
    DECLARE_SEGMENT(name##_yay0) \
    DECLARE_SEGMENT(name##_geo) \
    DECLARE_NOLOAD(name##_geo)

#define DECLARE_LEVEL_SCRIPT_SEGMENT(name) \
    DECLARE_SEGMENT(name) \
    DECLARE_NOLOAD(name)

#define DECLARE_LEVEL_SEGMENT(name) \
    DECLARE_LEVEL_SCRIPT_SEGMENT(name) \
    DECLARE_SEGMENT(name##_segment_7)

DECLARE_ACTOR_SEGMENT(group_global)
DECLARE_ACTOR_SEGMENT(group_btcm)
DECLARE_ACTOR_SEGMENT(group_vanilla)

DECLARE_SEGMENT(engine)
DECLARE_SEGMENT(behavior)
DECLARE_NOLOAD(behavior)
DECLARE_SEGMENT(menu_seg)
DECLARE_SEGMENT(framebuffers)
DECLARE_SEGMENT(assets)
extern u8 _menu_segSegmentStart[];
extern u8 _menu_segSegmentEnd[];
extern u8 _engineSegmentStart[];
extern u8 _engineSegmentBssEnd[];
extern u8 _mainSegmentStart[];
extern u8 _mainSegmentEnd[];
extern u8 _engineSegmentEnd[];
extern u8 _framebuffersSegmentBssStart[];
extern u8 _framebuffersSegmentBssEnd[];
extern u8 _zbufferSegmentBssStart[];
extern u8 _zbufferSegmentBssEnd[];
extern u8 _buffersSegmentBssStart[];
extern u8 _buffersSegmentBssEnd[];

DECLARE_LEVEL_SEGMENT(menu)
DECLARE_LEVEL_SCRIPT_SEGMENT(game)

DECLARE_SEGMENT(segment2_yay0)
DECLARE_SEGMENT(mb64_buttons_yay0)
DECLARE_SEGMENT(mb64_textures_yay0)

DECLARE_SEGMENT(water_skybox_yay0)
DECLARE_SEGMENT(ccm_skybox_yay0)
DECLARE_SEGMENT(clouds_skybox_yay0)
DECLARE_SEGMENT(bitfs_skybox_yay0)
DECLARE_SEGMENT(wdw_skybox_yay0)
DECLARE_SEGMENT(cloud_floor_skybox_yay0)
DECLARE_SEGMENT(ssl_skybox_yay0)
DECLARE_SEGMENT(bbh_skybox_yay0)
DECLARE_SEGMENT(bidw_skybox_yay0)
DECLARE_SEGMENT(bits_skybox_yay0)

DECLARE_SEGMENT(effect_yay0)

#ifdef VERSION_EU
DECLARE_SEGMENT(translation_de_yay0)
DECLARE_SEGMENT(translation_en_yay0)
DECLARE_SEGMENT(translation_fr_yay0)
#endif

//added for compatibility
DECLARE_SEGMENT(segment2_mio0)
DECLARE_SEGMENT(mb64_buttons_mio0)
DECLARE_SEGMENT(mb64_textures_mio0)

DECLARE_SEGMENT(water_skybox_mio0)
DECLARE_SEGMENT(ccm_skybox_mio0)
DECLARE_SEGMENT(clouds_skybox_mio0)
DECLARE_SEGMENT(bitfs_skybox_mio0)
DECLARE_SEGMENT(wdw_skybox_mio0)
DECLARE_SEGMENT(cloud_floor_skybox_mio0)
DECLARE_SEGMENT(ssl_skybox_mio0)
DECLARE_SEGMENT(bbh_skybox_mio0)
DECLARE_SEGMENT(bidw_skybox_mio0)
DECLARE_SEGMENT(bits_skybox_mio0)

DECLARE_SEGMENT(fire_mio0)
DECLARE_SEGMENT(spooky_mio0)
DECLARE_SEGMENT(generic_mio0)
DECLARE_SEGMENT(water_mio0)
DECLARE_SEGMENT(sky_mio0)
DECLARE_SEGMENT(snow_mio0)
DECLARE_SEGMENT(cave_mio0)
DECLARE_SEGMENT(machine_mio0)
DECLARE_SEGMENT(mountain_mio0)
DECLARE_SEGMENT(grass_mio0)
DECLARE_SEGMENT(outside_mio0)
DECLARE_SEGMENT(inside_mio0)
DECLARE_SEGMENT(effect_mio0)

#ifdef VERSION_EU
DECLARE_SEGMENT(translation_de_mio0)
DECLARE_SEGMENT(translation_en_mio0)
DECLARE_SEGMENT(translation_fr_mio0)
#endif

#endif

#endif // SEGMENT_SYMBOLS_H
