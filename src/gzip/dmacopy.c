
#include <ultra64.h>

/*-----------------------------------------------------------------------------
  DMA転送
	u32	  src_addr : 読み込み元カートリッジアドレス
	void* dest_addr: 出力先メインメモリアドレス
	u32	  size	   : 転送サイズ(バイト数)
-----------------------------------------------------------------------------*/

#define DMAREADBLOCK 8192

OSPiHandle *osCartRomHandle() {
	static OSPiHandle *cartHandle = NULL;

	if(cartHandle == NULL) {
		cartHandle = osCartRomInit();
	}

	return cartHandle;
}

u32 auRomDataRead(u32 src_addr, void* dest_addr, u32 size)
{
	static OSMesgQueue RomMessageQ;
	static OSMesg      RomMessageBuf;
	static int         initialized = 0;

	OSIoMesg dmaIoMesgBuf;
	u32 romaddr, memaddr, sizectr, readlen;

	if(!initialized) {
		osCreateMesgQueue(&RomMessageQ, &RomMessageBuf, 1);
		initialized = 1;
	}

	// CPUキャッシュの無効化
	osInvalDCache((void*)dest_addr, (s32)size);

	sizectr = size;
	romaddr = src_addr;
	memaddr = (u32)dest_addr;

	while(sizectr) {
		readlen = MIN(sizectr, DMAREADBLOCK);

		dmaIoMesgBuf.hdr.pri      = OS_MESG_PRI_NORMAL;
		dmaIoMesgBuf.hdr.retQueue = &RomMessageQ;
		dmaIoMesgBuf.dramAddr     = (void *)memaddr;
		dmaIoMesgBuf.devAddr      = romaddr;
		dmaIoMesgBuf.size         = readlen;

		osEPiStartDma(osCartRomHandle(), &dmaIoMesgBuf, OS_READ);

		romaddr += readlen;
		memaddr += readlen;
		sizectr -= readlen;

		// DMA転送終了まで待つ
		osRecvMesg(&RomMessageQ, NULL, OS_MESG_BLOCK);
	}

	return (u32)dest_addr + size;
}

