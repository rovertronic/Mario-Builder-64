#ifndef _GZIP_DMA_H_
#define _GZIP_DMA_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

void slidma(unsigned long dmasrc, char *dst, unsigned long dmasiz);

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif /* _GZIP_DMA_H_ */
