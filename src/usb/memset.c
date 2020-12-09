/*
=============================================================================
        Copyright (C) 1997-1999 NINTENDO Co.,Ltd.
        
        $RCSfile: memset.c,v $
        $Revision: 1.1 $
        $Date: 1999/04/14 07:18:41 $
=============================================================================
function name: memset
-----------------------------------------------------------------------------
format:   #include <string.h>
        void    *memset(void* dst, int c, size_t count);
argument:   dst   pointer of destination to be written
        c     byte data to be written
        count     the number of characters to be written  
return value:  pointer of destination to be written, dst  
explanation:   writes byte data c from the pointer dst indicates by the amount of count  
-----------------------------------------------------------------------------
*/
#include    <string.h>

void    *memset(void* dst, int c, size_t count)
{
    char    *p = (char *)dst;
    while(count--) *p++ = c;
    return  dst;
}
