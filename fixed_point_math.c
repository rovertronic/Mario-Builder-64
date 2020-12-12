// jk i dont think this file is needed lol
// update: it was needed :(

// hopefully I'll only need s15.16
// ^ clueless

f32 qtof(int q) {
	f32 lit = (float) ((q >> 16) & 0x7FFF);
	if (q < 0) lit = -lit;
	f32 dec = (float) ((float)(q & 0xFFFF) / (float)2^16);
	return lit + dec;
}

