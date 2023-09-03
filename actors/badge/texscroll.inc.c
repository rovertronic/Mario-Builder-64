void scroll_badge_ability_unlock_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 13;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	static int timeY;
	float amplitudeY = 1.0;
	float frequencyY = 1.0;
	float offsetY = 0.0;
	Vtx *vertices = segmented_to_virtual(badge_ability_unlock_mesh_layer_5_vtx_1);

	deltaY = (int)(amplitudeY * frequencyY * coss((frequencyY * timeY + offsetY) * (1024 * 16 - 1) / 6.28318530718) * 0x20);

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;	timeY += 1;
}

void scroll_actor_geo_badge() {
	scroll_badge_ability_unlock_mesh_layer_5_vtx_1();
};
