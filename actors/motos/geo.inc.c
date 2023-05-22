#define hmsShadow(a,b,c) GEO_SHADOW(c,b,a),
#define hmsBegin() GEO_OPEN_NODE(),
#define hmsTrans(x,y,z) GEO_TRANSLATE(0x00, x,y,z),
#define hmsScale(s) GEO_SCALE(0x00, (u32)(s * 65536)),
#define hmsJoint(l,dl,x,y,z) GEO_ANIMATED_PART(l, x, y, z, dl),
#define hmsEnd() GEO_CLOSE_NODE(),
#define hmsExit() GEO_END(),
#define hmsBboard(x,y,z) GEO_BILLBOARD(),
#define hmsGfx(l,dl) GEO_DISPLAY_LIST(l, dl),

#define RM_SURF LAYER_OPAQUE
#define RM_SPRITE LAYER_ALPHA

#define	softspriteON	1

#define Hierarchy const GeoLayout
/*-------------------------------------------------------------*/
/*	Hms data 			                                       */
/*-------------------------------------------------------------*/

Hierarchy RCP_HmsEnemymotos_basedata_A[] = {
 hmsShadow(100, 155, 1)
 hmsBegin()
  hmsTrans(0,-65,0)
  hmsBegin()
  hmsScale(0.25f)
    hmsBegin()
#if softspriteON
      hmsJoint(RM_SURF,NULL,0,279,0)  /* body_sprite(35) */
	  hmsBegin()
		hmsBboard(0,0,0)
	    hmsBegin()
		  hmsGfx(RM_SPRITE,RCP_motos_body)
	  	hmsEnd()
	  hmsEnd()
#else
      hmsJoint(RM_SURF,RCP_motos_basedata_A11,0,279,0)  /* body_sprite(35) */
#endif
      hmsBegin()
         hmsJoint(RM_SURF,NULL,0,0,0)  /* chn29(34) */
         hmsBegin()
            hmsJoint(RM_SURF,NULL,0,0,0)  /* jnt29_1(29) */
            hmsBegin()
               hmsJoint(RM_SURF,NULL,209,0,0)  /* chn33(25) */
               hmsBegin()
                  hmsJoint(RM_SURF,NULL,0,0,0)  /* jnt33_1(13) */
                  hmsBegin()
                     hmsJoint(RM_SURF,RCP_motos_LhandB,0,0,0)  /* cube5(1) */
                  hmsEnd()
               hmsEnd()
               hmsJoint(RM_SURF,NULL,208,1,0)  /* chn32(20) */
               hmsBegin()
                  hmsJoint(RM_SURF,NULL,0,0,0)  /* jnt32_1(14) */
                  hmsBegin()
                     hmsJoint(RM_SURF,RCP_motos_LhandA,0,0,0)  /* cube6(2) */
                  hmsEnd()
               hmsEnd()
               hmsJoint(RM_SURF,NULL,209,0,0)  /* eff29(11) */
               hmsBegin()
#if softspriteON
                  hmsJoint(RM_SURF,NULL,0,0,0)  /* R_arm_sprite(3) */
				  hmsBegin()
				  		hmsBboard(0,0,0)
						hmsBegin()
						  hmsGfx(RM_SPRITE, RCP_motos_arm)
						hmsEnd()
				  hmsEnd()
#else
                  hmsJoint(RM_SURF,RCP_motos_basedata_A0,0,0,0)  /* L_arm_sprite(0) */
#endif
               hmsEnd()
            hmsEnd()
         hmsEnd()
         hmsJoint(RM_SURF,NULL,0,0,0)  /* chn31(33) */
         hmsBegin()
            hmsJoint(RM_SURF,NULL,0,0,0)  /* jnt31_1(30) */
            hmsBegin()
               hmsJoint(RM_SURF,NULL,208,1,0)  /* chn35(26) */
               hmsBegin()
                  hmsJoint(RM_SURF,NULL,0,0,0)  /* jnt35_1(15) */
                  hmsBegin()
                     hmsJoint(RM_SURF,RCP_motos_RhandA,0,0,0)  /* cube3(4) */
                  hmsEnd()
               hmsEnd()
               hmsJoint(RM_SURF,NULL,209,0,0)  /* chn37(21) */
               hmsBegin()
                  hmsJoint(RM_SURF,NULL,0,0,0)  /* jnt37_1(16) */
                  hmsBegin()
                     hmsJoint(RM_SURF,RCP_motos_RhandB,0,0,0)  /* cube4(5) */
                  hmsEnd()
                  GEO_ASM(0, geo_update_held_mario_pos),
               hmsEnd()
               hmsJoint(RM_SURF,NULL,209,0,0)  /* eff31(12) */
               hmsBegin()

#if softspriteON
                  hmsJoint(RM_SURF,NULL,0,0,0)  /* R_arm_sprite(3) */
				  hmsBegin()
				    hmsBboard(0,0,0)
				    hmsBegin()
					  hmsGfx(RM_SPRITE, RCP_motos_arm)
				    hmsEnd()
				  hmsEnd()
#else
                  hmsJoint(RM_SURF,RCP_motos_basedata_A3,0,0,0)  /* R_arm_sprite(3) */
#endif


               hmsEnd()

            hmsEnd()
         hmsEnd()
         hmsJoint(RM_SURF,NULL,87,0,0)  /* chn38(32) */
         hmsBegin()
            hmsJoint(RM_SURF,NULL,0,0,0)  /* jnt38_1(27) */
            hmsBegin()
               hmsJoint(RM_SURF,NULL,181,0,0)  /* jnt38_2(22) */
               hmsBegin()
                  hmsJoint(RM_SURF,NULL,71,0,0)  /* jnt38_3(17) */
                  hmsBegin()
                     hmsJoint(RM_SURF,RCP_motos_Lfoot,0,0,0)  /* cube2(6) */
                  hmsEnd()

#if softspriteON
                  hmsJoint(RM_SURF, NULL,0,0,0)  /* L_foot_sprite(7) */
				  hmsBegin()
				    hmsBboard(0,0,0)
				    hmsBegin()
					  hmsGfx(RM_SPRITE, RCP_motos_leg)
				    hmsEnd()
				  hmsEnd()
#else
                  hmsJoint(RM_SURF,RCP_motos_basedata_A7,0,0,0)  /* L_foot_sprite(7) */
#endif

               hmsEnd()
            hmsEnd()
         hmsEnd()
         hmsJoint(RM_SURF,NULL,-87,0,0)  /* chn40(31) */
         hmsBegin()
            hmsJoint(RM_SURF,NULL,0,0,0)  /* jnt40_1(28) */
            hmsBegin()
               hmsJoint(RM_SURF,NULL,181,0,0)  /* jnt40_2(23) */
               hmsBegin()
                  hmsJoint(RM_SURF,NULL,71,0,0)  /* jnt40_3(18) */
                  hmsBegin()
                     hmsJoint(RM_SURF,RCP_motos_Rfoot,0,0,0)  /* cube7(8) */
                  hmsEnd()

#if softspriteON
                  hmsJoint(RM_SURF,NULL,0,0,0)  /* R_foot_sprite(9) */
				  hmsBegin()
				      hmsBboard(0,0,0)
					  hmsBegin()
					 	 hmsGfx(RM_SPRITE, RCP_motos_leg)
				      hmsEnd()
				  hmsEnd()
#else
                  hmsJoint(RM_SURF,RCP_motos_basedata_A9,0,0,0)  /* R_foot_sprite(9) */
#endif


               hmsEnd()
            hmsEnd()
         hmsEnd()
         hmsJoint(RM_SURF,NULL,0,178,0)  /* chn41(24) */
         hmsBegin()
            hmsJoint(RM_SURF,NULL,0,0,0)  /* jnt41_1(19) */
            hmsBegin()
               hmsJoint(RM_SURF,RCP_motos_head,0,0,0)  /* sphere3(10) */
            hmsEnd()
         hmsEnd()
      hmsEnd()
   hmsEnd()
  hmsEnd()
 hmsEnd()
 hmsExit()
};
