// pole_base.inc.c

void bhv_pole_base_loop(void) {
    if (
        o->oPosY - 10.0f < gMarioObject->oPosY
        && gMarioObject->oPosY < o->oPosY + o->hitboxHeight + 30.0f
        && o->oTimer > 10
        && !(gMarioState->action & MARIO_PUNCHING)
    ) {
        cur_obj_push_mario_away(70.0f);
    }
}

//Oscilation
void bhv_Tree_Osc(void) {
    //init

    if (o->oAction == 0) {
        o->oVelX = o->oBehParams2ndByte-128;
        o->oVelZ = o->oBehParams2ndByte-128;
        o->oAction = 1;
        }
    if (o->oAction == 1) {
        if (((gCurrentObject->oBehParams >> 24) & 0xFF) == 0) {
            o->oPosX += o->oVelX;

            if (o->oPosX > o->oHomeX) {
                o->oVelX --;
                }
                else
                {
                o->oVelX ++;
                }
            }
            else
            {
            o->oPosZ += o->oVelZ;

            if (o->oPosZ > o->oHomeZ) {
                o->oVelZ --;
                }
                else
                {
                o->oVelZ ++;
                }
            }
        }
    }
