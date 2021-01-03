#ifndef __GZIP_H__
#define	__GZIP_H__

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#define INBUFSIZ	4096	// input buffer size
#define WSIZE		0x8000

typedef struct {
	u8 *	next_addr;
	u32	rest_size;
} FILE_HND;

#define get_byte()  (inptr < insize ? inbuf[inptr++] : fill_inbuf(0))
#define try_byte()  (inptr < insize ? inbuf[inptr++] : fill_inbuf(1))

extern unsigned int insize;	// valid bytes in inbuf
extern unsigned int inptr;	// index of next byte to be processed in inbuf
extern unsigned int outcnt;	// bytes in output buffer
extern	u8	inbuf[];		// input buffer
extern	u8	*op;		// Sliding window and suffix table

extern int	inflate(void);
extern int	fill_inbuf(int eof_ok);
extern void	flush_window(void);
extern void dma_read(u8 *dest, u8 *srcStart, u8 *srcEnd);

#endif
