s16 time=0;

void scroll_jrb_sky_cloud_mesh_vtx_0() {
	int i = 0;
	int count = 91;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	static int timeY;
	float amplitudeY = 0.25;
	float frequencyY = 0.25;
	float offsetY = 0.0;
	Vtx *vertices = segmented_to_virtual(jrb_sky_cloud_mesh_vtx_0);

	deltaX = (int)(0.25 * 0x20) % width;
	deltaY = (int)(amplitudeY * frequencyY * coss((frequencyY * timeY + offsetY) * (1024 * 16 - 1) / 6.28318530718) * 0x20);

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}
	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	time += 0x70;

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
		vertices[i].n.tc[1] += deltaY;
		vertices[i].n.ob[1] = 27*((sins(4*time-vertices[i].n.ob[2]*100)) - (sins(4*time-vertices[i].n.ob[0]*100)))-20;
	}
	currentX += deltaX;	currentY += deltaY;	timeY += 1;
}

void scroll_jrb_level_dl_jrb_sky() {
	scroll_jrb_sky_cloud_mesh_vtx_0();
}