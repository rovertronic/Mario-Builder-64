#include "src/game/envfx_snow.h"

extern Gfx *geo_badge_material(s32 callContext, struct GraphNode *node, void *context);

const GeoLayout badge_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 204, 50),
		GEO_OPEN_NODE(),
			GEO_ASM(0, geo_badge_material),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT, badge_ability_unlock_mesh_layer_5),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, badge_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
