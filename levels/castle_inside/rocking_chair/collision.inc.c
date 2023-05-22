const Collision rocking_chair_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(4),
	COL_VERTEX(54, 90, -63),
	COL_VERTEX(-51, 85, -63),
	COL_VERTEX(-51, 85, 43),
	COL_VERTEX(54, 90, 43),
	COL_TRI_INIT(SURFACE_DEFAULT, 2),
	COL_TRI(0, 1, 2),
	COL_TRI(0, 2, 3),
	COL_TRI_STOP(),
	COL_END()
};
