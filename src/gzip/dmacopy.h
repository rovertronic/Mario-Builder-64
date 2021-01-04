
#if !defined(_DMACOPY_H_)
#define _DMACOPY_H_

extern OSPiHandle *osCartRomHandle();
extern u32 auRomDataRead(u32 src_addr, void* dest_addr, u32 size);

#endif // _DMACOPY_H_
