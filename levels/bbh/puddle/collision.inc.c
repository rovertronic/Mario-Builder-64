const Collision puddle_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(6),
	COL_VERTEX(4, 0, 2),
	COL_VERTEX(4, 0, -2),
	COL_VERTEX(0, 0, -5),
	COL_VERTEX(-4, 0, -2),
	COL_VERTEX(-4, 0, 2),
	COL_VERTEX(0, 0, 5),
	COL_TRI_INIT(SURFACE_INSTANT_QUICKSAND, 4),
	COL_TRI(0, 1, 2),
	COL_TRI(2, 3, 4),
	COL_TRI(4, 5, 0),
	COL_TRI(2, 4, 0),
	COL_TRI_STOP(),
	COL_END()
};
