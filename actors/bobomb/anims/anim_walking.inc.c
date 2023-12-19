static const s16 bobomb_anim_walking_values[276] = {
	-2,     -2,     -2,     -1,     0,      0,      0,      
	1,      1,      2,      2,      2,      2,      2,      
	1,      1,      0,      0,      0,      -1,     -1,     
	-2,     60,     61,     62,     63,     64,     65,     
	64,     64,     62,     61,     61,     60,     61,     
	61,     62,     64,     64,     65,     64,     64,     
	63,     62,     61,     61,     60,     0,      16374,  
	16304,  16076,  15504,  -13761, -16519, 13459,  18014,  
	16996,  16627,  16433,  16368,  16429,  16580,  16848,  
	17334,  19334,  14622,  -16484, -15282, -17871, 15901,  
	16186,  16330,  16374,  -15340, -15467, -15769, -16129, 
	-16335, -16217, -16451, -16197, -15883, -15571, -15331, 
	-15236, -15309, -15495, -15750, -16028, -16284, -16483, 
	-16208, -16293, -16521, -15954, -15659, -15431, -15340, 
	16914,  16942,  17062,  17488,  -18940, -16322, 19091,  
	14368,  15215,  15432,  15520,  15545,  15518,  15455,  
	15312,  14974,  13126,  17984,  -16325, -17413, -14699, 
	17184,  17003,  16932,  16914,  0,      26917,  26482,  
	25289,  23509,  21306,  18851,  16312,  13858,  11655,  
	9874,   8681,   8247,   8562,   9436,   10770,  12461,  
	14407,  16506,  18657,  20756,  22702,  24392,  25728,  
	26602,  26917,  0,      -5,     -14,    -28,    -45,    
	-60,    -73,    -78,    -77,    -65,    -41,    0,      
	131,    363,    596,    729,    724,    637,    518,    
	413,    318,    209,    105,    30,     0,      0,      
	0,      0,      0,      0,      0,      0,      0,      
	0,      0,      0,      0,      -2,     -7,     -8,     
	0,      21,     56,     87,     101,    90,     64,     
	35,     9,      0,      -22954, -22814, -22423, -21824, 
	-21057, -20168, -19197, -18188, -17181, -16222, -15351, 
	-14610, -13859, -13135, -12760, -13053, -14418, -16580, 
	-18834, -20475, -21437, -22140, -22610, -22873, -22954, 
	0,      8455,   8844,   9910,   11503,  13470,  15666,  
	17935,  20128,  22097,  23689,  24755,  25143,  24863,  
	24081,  22888,  21377,  19636,  17761,  15839,  13963,  
	12223,  10712,  9520,   8737,   8455,   0,      -14401, 
	-13741, -12569, -12091, -13556, -15772, -17654, -19507, 
	-20969, -22003, -22645, -22642, -22153, -21529, -20798, 
	-19995, -19145, -18283, -17436, -16636, -15913, -15298, 
	-14820, -14511, -14401, 
};

static const u16 bobomb_anim_walking_indicies[36] = {
	22,  0,   25,  22,  1,   47,  25,  48,  25,  73,  25,  98,  
	1,   123, 1,   123, 25,  124, 25,  149, 25,  174, 25,  199, 
	1,   224, 1,   224, 25,  225, 1,   250, 1,   250, 25,  251, 
	
};

static const struct Animation bobomb_anim_walking = {
	0,
	0,
	0,
	0,
	25,
	5,
	bobomb_anim_walking_values,
	bobomb_anim_walking_indicies,
	0,
};
