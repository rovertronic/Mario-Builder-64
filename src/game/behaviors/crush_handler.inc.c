void bhv_crush_handler(void) {
    if (o->oTimer > 30) {
        mark_obj_for_deletion(o);
    }
    o->oInteractStatus = INT_NONE;
}
