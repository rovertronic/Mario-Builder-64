/*
=============================================================================
        Copyright (C) 1997-1999 NINTENDO Co.,Ltd.
        
        $RCSfile: memcmp.c,v $
        $Revision: 1.1 $
        $Date: 1999/04/14 07:18:40 $
=============================================================================
function name: memcmp
-----------------------------------------------------------------------------
format:   #include <string.h>
        int memcmp(const void *buf1, const void *buf2, size_t count)
argument:   buf1   pointer to be compared 
        buf2       pointer to be compared
        count      the number of bytes to be compared
return value: if less than 0   buf1 is smaller than buf2  
        if 0       buf1 is equal to buf2  
        if more than 0   buf1 is larger than buf2  
explanation:  compares the contents of pointer buf1 and pointer buf2 by the number of count bytes
-----------------------------------------------------------------------------
*/
#include    <string.h>

int memcmp(const void *buf1, const void *buf2, size_t count)
{
    char    *b1 = (char *)buf1, *b2 = (char *)buf2;
    while(count)    {
        if (*b1 != *b2)     return  *b1 - *b2;
        b1 ++;
        b2 ++;
        count--;
    }
    return  0;
}
