#include "src/game/envfx_snow.h"

const GeoLayout bowser_bomb_geo[] = {
   GEO_CULLING_RADIUS(183),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bomb_spikes_mesh_layer_1),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(LAYER_ALPHA, 0, 0, 0, bomb_bomb_billboard_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bomb_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bomb_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
