#ifndef _GZIP_DMA_H_
#define _GZIP_DMA_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

void slidma(u8 *src_addr, u8 *dst_addr, u32 size);

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif /* _GZIP_DMA_H_ */
