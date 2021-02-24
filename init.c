#include <ultra64.h>
#include <PR/gs2dex.h>
#include "init.h"

void s2d_init(void) {
	gSPLoadUcode(gdl_head++, s2d_text, s2d_data);
}

void s2d_stop(void) {
	gSPLoadUcode(gdl_head++, zex_text, zex_data);
	my_rdp_init();
	my_rsp_init();
}

