#include <ultra64.h>
#include <PR/os_internal_error.h>
#include <stdarg.h>
#include <string.h>
#include "segments.h"

struct MapEntry {
	u32 addr;
	u32 nm_offset;
	u32 nm_len;
	u32 pad;
};
extern u8 gMapStrings[];
extern struct MapEntry gMapEntries[];
extern u32 gMapEntrySize;
extern u8 _mapDataSegmentRomStart[];


// code provided by Wiseguy
static s32 headless_dma(u32 devAddr, void *dramAddr, u32 size)
{
    register u32 stat;
    stat = IO_READ(PI_STATUS_REG);
	while (stat & (PI_STATUS_IO_BUSY | PI_STATUS_DMA_BUSY)) {
	    stat = IO_READ(PI_STATUS_REG);
	}
    IO_WRITE(PI_DRAM_ADDR_REG, K0_TO_PHYS(dramAddr));
    IO_WRITE(PI_CART_ADDR_REG, K1_TO_PHYS((u32)osRomBase | devAddr));
    IO_WRITE(PI_WR_LEN_REG, size - 1);
    return 0;
}
static u32 headless_pi_status(void)
{
    return IO_READ(PI_STATUS_REG);
}
// end of code provided by Wiseguy


void map_data_init(void) {
	headless_dma(_mapDataSegmentRomStart, 0x80700000, 0x100000);
	while (headless_pi_status() & (PI_STATUS_DMA_BUSY | PI_STATUS_ERROR));
}

char *parse_map(u32 pc) {
	u32 i;

	for (i = 0; i < gMapEntrySize; i++) {
		if (gMapEntries[i].addr >= pc) break;
	}

	if (i == gMapEntrySize - 1) {
		return "Unknown";
	} else {
		return (char*) ((u32)gMapStrings + gMapEntries[i - 1].nm_offset);
	}
}
