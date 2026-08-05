#include <ultra64.h>
#include "sm64.h"
#include "surface_terrains.h"
#include "geo_commands.h"

#include "make_const_nonconst.h"

// Note: This bin does not use bin IDs, unlike the other segmented bins.
#include "bubble/model.inc.c"

#include "walk_smoke/model.inc.c"

#include "burn_smoke/model.inc.c"

#include "small_water_splash/model.inc.c"

#include "water_wave/model.inc.c"

#include "sparkle/model.inc.c"

#include "water_splash/model.inc.c"

#include "white_particle_small/model.inc.c"

#include "sparkle_animation/model.inc.c"

#include "koopa/model.inc.c"
#include "koopa/anims/data.inc.c"
#include "koopa/anims/table.inc.c"

#include "piranha_plant/model.inc.c"
#include "piranha_plant/anims/data.inc.c"
#include "piranha_plant/anims/table.inc.c"

#include "whomp/model.inc.c"
#include "whomp/anims/data.inc.c"
#include "whomp/anims/table.inc.c"
#include "whomp/collision.inc.c"

#include "chillychief/model.inc.c"
#include "chillychief/anims/data.inc.c"
#include "chillychief/anims/table.inc.c"

#include "lakitu_enemy/model.inc.c"
#include "lakitu_enemy/anims/data.inc.c"
#include "lakitu_enemy/anims/table.inc.c"

#include "spiny_egg/model.inc.c"
#include "spiny_egg/anims/data.inc.c"
#include "spiny_egg/anims/table.inc.c"

#include "spiny/model.inc.c"
#include "spiny/anims/data.inc.c"
#include "spiny/anims/table.inc.c"

#include "moneybag/model.inc.c"
#include "moneybag/anims/data.inc.c"
#include "moneybag/anims/table.inc.c"

#include "noteblock/model.inc.c"
#include "noteblock/collision.inc.c"

#include "top/model.inc.c"
#include "maker/model.inc.c"
#include "maker/minecrafttex.inc.c"

// Just a single idle anim for editor
#include "mario_btcm/anims/data.inc.c"
#include "mario_btcm/anims/table.inc.c"

#include "sb_cube/model.inc.c"   // Cursor
#include "lev_edge/model.inc.c"  // Red boundary grid
#include "spawn/model.inc.c"
#include "mm_btn/model.inc.c"

#include "bigpainting2/model.inc.c"
#include "thwomp/model.inc.c"
#include "thwomp/collision.inc.c"

#include "bullet_bill/model.inc.c"

#include "heave_ho/model.inc.c"
#include "heave_ho/anims/data.inc.c"
#include "heave_ho/anims/table.inc.c"
#include "blaster/model.inc.c"
#include "blaster/collision.inc.c"

#include "mr_i_eyeball/model.inc.c"
#include "mr_i_iris/model.inc.c"

#include "snufit/model.inc.c"

#include "scuttlebug/model.inc.c"
#include "scuttlebug/anims/data.inc.c"
#include "scuttlebug/anims/table.inc.c"

#include "boo/model.inc.c"

#include "spindrift/model.inc.c"
#include "spindrift/anims/data.inc.c"
#include "spindrift/anims/table.inc.c"

#include "snowman/model.inc.c"
#include "snowman/anims/data.inc.c"
#include "snowman/anims/table.inc.c"

#include "actors/grindel/collision.inc.c"
#include "actors/grindel/model.inc.c"
#include "loopingp/model.inc.c"
#include "loopingp/collision.inc.c"

#include "motos/anims/anim.inc.c"
#include "motos/model.inc.c"

#include "bully/model.inc.c"
#include "bully/anims/data.inc.c"
#include "bully/anims/table.inc.c"

#include "new_cull_marker/model.inc.c"
#include "skeeter/model.inc.c"
#include "skeeter/anims/data.inc.c"
#include "skeeter/anims/table.inc.c"
#include "gooner/model.inc.c"
#include "gooner/collision.inc.c"
#include "spooner/model.inc.c"
#include "spooner/collision.inc.c"

#include "pokey/model.inc.c"
#include "timedbox/model.inc.c"
#include "onoffswitch/model.inc.c"
#include "onoffblock1/model.inc.c"
#include "onoffblock2/model.inc.c"
#include "onoffbutton/collision.inc.c"
#include "onoffblock/collision.inc.c"
#include "onoffbutton/model.inc.c"
#include "water_level_diamond/model.inc.c"
#include "woodplat/collision.inc.c"
#include "woodplat/model.inc.c"
#include "rfbox/model.inc.c"
#include "fatplat/model.inc.c"
#include "conveyor/collision.inc.c"
#include "conveyor/model.inc.c"
#include "imbue/model.inc.c"
#include "imbues/model.inc.c"
#include "conveyor_half/model.inc.c"
#include "conveyor_half/collision.inc.c"
#include "conveyor_slope/model.inc.c"
#include "conveyor_slope/collision.inc.c"
#include "conveyor_dslope/model.inc.c"
#include "conveyor_dslope/collision.inc.c"
#include "imbuec/model.inc.c"
#include "imbuet/model.inc.c"

#include "mist/model.inc.c"
#include "explosion/model.inc.c"
#include "coin/model.inc.c"
#include "flame/model.inc.c"
#include "pebble/model.inc.c"
#include "leaves/model.inc.c"
#include "power_meter/model.inc.c"
#ifdef BREATH_METER
#include "breath_meter/model.inc.c"
#endif
#include "star/model.inc.c"
#include "sand/model.inc.c"
#include "dirt/model.inc.c"
#include "transparent_star/model.inc.c"
#include "white_particle/model.inc.c"
#include "wooden_signpost/model.inc.c"
#include "wooden_signpost/collision.inc.c"
#include "tree/model.inc.c"

#include "blue_coin_switch/model.inc.c"
#include "blue_coin_switch/collision.inc.c"
#include "amp/model.inc.c"
#include "amp/anims/data.inc.c"
#include "amp/anims/table.inc.c"
#include "chuckya/model.inc.c"
#include "chuckya/anims/data.inc.c"
#include "chuckya/anims/table.inc.c"
#include "purple_switch/model.inc.c"
#include "purple_switch/collision.inc.c"
#include "checkerboard_platform/model.inc.c"
#include "checkerboard_platform/collision.inc.c"
#include "heart/model.inc.c"
#include "flyguy/model.inc.c"
#include "flyguy/anims/data.inc.c"
#include "flyguy/anims/table.inc.c"
#include "breakable_box/model.inc.c"
#include "breakable_box/collision.inc.c"
#include "goomba/model.inc.c"
#include "goomba/anims/data.inc.c"
#include "goomba/anims/table.inc.c"
#include "bobomb/model.inc.c"
#include "bobomb/anims/data.inc.c"
#include "bobomb/anims/table.inc.c"
#include "bowling_ball/model.inc.c"
#include "exclamation_box_outline/collision.inc.c"
#include "koopa_shell/model.inc.c"
