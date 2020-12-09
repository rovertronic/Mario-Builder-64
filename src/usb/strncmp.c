/*
=============================================================================
        Copyright (C) 1997-1999 NINTENDO Co.,Ltd.
        
        $RCSfile: strncmp.c,v $
        $Revision: 1.1 $
        $Date: 1999/04/14 07:18:42 $
=============================================================================
function name: strncmp
-----------------------------------------------------------------------------
format :   #include <string.h>
        int strncmp(const char *str1, const char *str2, int n)
argument:   str1   character string buffer to be compared
        	str2   character string buffer to be compared
        	n   	 character number to be compared
return value: if less than 0,   str1 is smaller than str2 
        	  if 0       	  str1 is equal to str2 
        	  if more than 0,   str1 is larger than str2 
explanation:   compares character string, str1 with character string, str2 by
		   n character  
-----------------------------------------------------------------------------
*/
#include    <string.h>

int strncmp(const char *str1, const char *str2, int n)
{
    char    c1 = 1,c2;
    while(c1 && n--)    {
        c1=*str1++;
        c2=*str2++;
        if (c1 != c2)   return c1 - c2;
    }
    return 0;
}
