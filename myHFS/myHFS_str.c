#include "myHFS_str.h"
void strdelete(char *p)
{
    for (; *(p + 1) != '\0'; p++)
    {
        *p = *(p + 1);
    }
    *p = '\0';
}
void insert(char *p, char ch)
{
    char *p1 = p;
    while (*p != '\0') //移到末尾
    {
        p++;
    }
    while (p1 != p)
    {
        *(p + 1) = *p;
        p--;
    }
    *++p = ch;
}

int strcut(char *str, char *front, char *rear, char *re)
{
    char *p1, *p2;
		
    p1 = strstr(str, front);
		if(p1==NULL)
		{
			return 0;
		}
    p1 += strlen(front);
    p2 = strstr(str, rear);
		if(p2==NULL)
		{
			return 0;
		}
		if(front==rear)
		{
			re="";
			return 0;
		}
    while (p1 != p2)
    {
        *re++ = *p1++;
    }
    *re = '\0';
}