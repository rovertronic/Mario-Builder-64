#include "tile.h"
#include "mb64_textures.h"

#include <PR/gbi.h>
#include "game/memory.h"
#include "game/tile_scroll.h"

extern u32 gGlobalTimer;

static Gfx *mb64_find_gfx_cmd(Gfx *dl, u8 op) {
    Gfx *found = NULL;

    if (dl == NULL) {
        return NULL;
    }
    for (; (u8)(dl->words.w0 >> 24) != G_ENDDL; dl++) {
        if ((u8)(dl->words.w0 >> 24) == op) {
            found = dl;
        }
    }
    return found;
}

static void mb64_shift_dl(Gfx *dl, s32 ds, s32 dt) {
    Gfx *tileSize = mb64_find_gfx_cmd(dl, G_SETTILESIZE);

    if (tileSize == NULL) {
        return;
    }
    if (ds) {
        shift_s(tileSize, 0, PACK_TILESIZE(0, ds));
    }
    if (dt) {
        shift_t(tileSize, 0, PACK_TILESIZE(0, dt));
    }
}

static void mb64_scroll_tex(const struct texture_define *want, s32 ds, s32 dt) {
    struct mb64_theme *theme = &mb64_theme_table[mb64_lopt_theme];
    s32 i;

    for (i = 0; i < NUM_MATERIALS_PER_THEME; i++) {
        if (mb64_mat_table[theme->mats[i].mat].tex == want) {
            mb64_shift_dl(mb64_material_gfx.mats[i].tex, ds, dt);
        }
        if (mb64_mat_table[theme->mats[i].topmat].tex == want) {
            mb64_shift_dl(mb64_material_gfx.mats[i].toptex, ds, dt);
        }
    }
    if (mb64_mat_table[theme->pole].tex == want) {
        mb64_shift_dl(mb64_material_gfx.pole, ds, dt);
    }
    if (mb64_water_texs[theme->water] == want) {
        mb64_shift_dl(mb64_material_gfx.water, ds, dt);
    }
}

static void mb64_set_img_tex(const struct texture_define *want, uintptr_t img) {
    struct mb64_theme *theme = &mb64_theme_table[mb64_lopt_theme];
    s32 i;

    for (i = 0; i < NUM_MATERIALS_PER_THEME; i++) {
        if (mb64_mat_table[theme->mats[i].mat].tex == want) {
            Gfx *setImg = mb64_find_gfx_cmd(mb64_material_gfx.mats[i].tex, G_SETTIMG);
            if (setImg != NULL) {
                setImg->words.w1 = img;
            }
        }
        if (mb64_mat_table[theme->mats[i].topmat].tex == want) {
            Gfx *setImg = mb64_find_gfx_cmd(mb64_material_gfx.mats[i].toptex, G_SETTIMG);
            if (setImg != NULL) {
                setImg->words.w1 = img;
            }
        }
    }
    if (mb64_mat_table[theme->pole].tex == want) {
        Gfx *setImg = mb64_find_gfx_cmd(mb64_material_gfx.pole, G_SETTIMG);
        if (setImg != NULL) {
            setImg->words.w1 = img;
        }
    }
    if (mb64_water_texs[theme->water] == want) {
        Gfx *setImg = mb64_find_gfx_cmd(mb64_material_gfx.water, G_SETTIMG);
        if (setImg != NULL) {
            setImg->words.w1 = img;
        }
    }
}

void scroll_mb64_textures(void) {
    const struct texture_define *waterDef = segmented_to_virtual(&mb64_tex_MCWater);
    const struct texture_define *lavaDef = segmented_to_virtual(&mb64_tex_MCLava);
    u8 *waterTex;
    u8 *lavaTex;

    mb64_scroll_tex(&mb64_tex_ServerAcid, 1, 1);
    mb64_scroll_tex(&mb64_tex_GreenWater, 1, 1);
    mb64_scroll_tex(&mb64_tex_Void, 1, 1);
    mb64_scroll_tex(&mb64_tex_Quicksand, 1, 1);
    mb64_scroll_tex(&mb64_tex_BurningIce, 1, 1);
    mb64_scroll_tex(&mb64_tex_Water, 1, 1);
    mb64_scroll_tex(&mb64_tex_Lava, 1, 1);
    mb64_scroll_tex(&mb64_tex_VanillaLava, 1, 1);

    {
        static int cur_interval_retro_lava = 10;
        if (--cur_interval_retro_lava <= 0) {
            mb64_scroll_tex(&mb64_tex_RetroLava, 5, 5);
            cur_interval_retro_lava = 10;
        }
    }
    {
        static int cur_interval_retro_water = 10;
        if (--cur_interval_retro_water <= 0) {
            mb64_scroll_tex(&mb64_tex_RetroWater, 5, 5);
            cur_interval_retro_water = 10;
        }
    }
    {
        static int cur_interval_mc_flowing_lava = 4;
        if (--cur_interval_mc_flowing_lava <= 0) {
            mb64_scroll_tex(&mb64_tex_MCFlowingLava, 0, 68);
            cur_interval_mc_flowing_lava = 4;
        }
    }

    waterTex = segmented_to_virtual(waterDef->ci.tex);
    waterTex += (16 * 8) * ((gGlobalTimer / 2) % 32);
    mb64_set_img_tex(&mb64_tex_MCWater, (uintptr_t)waterTex);

    lavaTex = segmented_to_virtual(lavaDef->ci.tex);
    lavaTex += (16 * 16) * ((gGlobalTimer / 2) % 38);
    mb64_set_img_tex(&mb64_tex_MCLava, (uintptr_t)lavaTex);
    mb64_set_img_tex(&mb64_tex_MCFlowingLava, (uintptr_t)lavaTex);
}
