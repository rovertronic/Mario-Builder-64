// reds_star_marker.inc.c
// Filename is abbreviated to prevent compiler seg fault

void bhv_red_coin_star_marker_init(void) {
    struct Surface *floor;
    find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);
    if (floor && floor->type == SURFACE_DEATH_PLANE) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
    o->header.gfx.scale[2] = 0.75f;
}
