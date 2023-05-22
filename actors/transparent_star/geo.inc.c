const GeoLayout star_opt1[] = {
   GEO_DISPLAY_LIST(LAYER_TRANSPARENT, transparent_star_seg3_dl_body),
   GEO_RETURN(),
};

const GeoLayout star_opt2[] = {
   GEO_DISPLAY_LIST(LAYER_TRANSPARENT, transparent_star_black),
   GEO_RETURN(),
};

// 0x16000F6C
const GeoLayout transparent_star_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0x9B, 100),
   GEO_OPEN_NODE(),
      GEO_SCALE(0x00, 16384),
      GEO_OPEN_NODE(),
         GEO_SWITCH_CASE(2, geo_switch_anim_state),
         GEO_OPEN_NODE(),
            GEO_BRANCH(1, star_opt1),
			   GEO_BRANCH(1, star_opt2),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
