/*
=============================================================================
        Copyright (C) 1997-1999 NINTENDO Co.,Ltd.
        
        $RCSfile: strcat.c,v $
        $Revision: 1.1 $
        $Date: 1999/04/14 07:18:41 $
=============================================================================
function name: strcat
-----------------------------------------------------------------------------
format:   #include <string.h>
        char  *strcat(char *str1, const char *str2);
argument:   str1   character string buffer to be added  
        	str2   character string buffer to add
return value: pointer of str1 
explanation:  adds character string, str2 to the end of character string, str1  
-----------------------------------------------------------------------------
*/
#include    <string.h>

char  *strcat(char *str1, const char *str2)
{
    char *p;
    p = str1;
    while(*p) p++;
    while(*str2) *p++ = *str2++;
    *p = '\0';
    return  str1;
}
