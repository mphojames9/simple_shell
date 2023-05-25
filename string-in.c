#include "shell.h"
/**
* strlen_char - string length
* @s: string whose length to check
*
* Return: integer string length
*/
int strlen_char(char *s)
{
int i = 0;
if (!s)
return (0);
while (*s++)
i++;
return (i);
}
/**
* strcmp_char - lexicogarphic two strangs.
*
* @s1: 1st strang
* @s2: 2nd strang
*
* Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
*/
int strcmp_char(char *s1, char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
return (*s1 - *s2);
s1++;
s2++;
}
if (*s1 == *s2)
return (0);
else
return (*s1 < *s2 ? -1 : 1);
}
/**
* starts_with - checks if needle begins with haystack
*
* @haystack: string to search
* @needle: the substring to find
*
* Return: location of next char of haystack or NULL
*/
char *starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}
/**
* _strcat - two strings
*
* @dest: buffer destination
* @src: buffer source
*
* Return: destination buffer
*/
char *_strcat(char *dest, char *src)
{
char *ret = dest;
while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (ret);
}
