// lll_sinking_rock_block.inc.c

void bhv_lll_sinking_rock_block_loop(void) {
    // lll_octagonal_mesh_find_y_offset(&o->oSinkWhenSteppedOnTimer, &o->oSinkWhenSteppedOnYOffsetFromHome, 124, -110);
    // o->oGraphYOffset = 0.0f;
    // o->oPosY = o->oHomeY + o->oSinkWhenSteppedOnYOffsetFromHome;

    //nintendo this sucks i don't care how sophisticated you think you are
    //this is counter productive

    switch (o->oAction) {
        case 0://ide, go up an down

        o->oPosY = -20.0f + o->oHomeY + (sins(o->oTimer*0x200) * 20.0f);

        if (cur_obj_is_mario_on_platform()) {
            o->oAction ++;
            }
        break;
        case 1://sink when mario is on
        o->oPosY -= 1.1f;
        o->oVelY = -1.1f;
        if (!cur_obj_is_mario_on_platform()) {
            o->oAction ++;
            }
        break;
        case 2://rise back up
        o->oPosY += 2.0f;
        o->oVelY += -2.0f;
        if (cur_obj_is_mario_on_platform()) {
            o->oAction = 1;
            o->oTimer = 0;
            }

        if (o->oPosY > o->oHomeY-20.0f) {
            o->oAction = 0;
            o->oTimer = 0;
            }
        break;
        }
}
