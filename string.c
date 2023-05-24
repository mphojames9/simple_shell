#include "shell.h"
/**
* strlen_length - returns the length for string
* @s: the string whose length to be checking
* Return: integer length for the string
*/
int strlen_length(char *s)
{
int i = 0;
if (!s)
return (0);
while (*s++)
i++;
return (i);
}
/**
* strcmp_lexicogarphic - lexicogarphic comparing of two strangs.
* @s1: the first strang strung
* @s2: the second strang strung
* Return: this as negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
*/
int strcmp_lexicogarphic(char *s1, char *s2)
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
* starts_with - checks whether the needle starts with haystack
* @haystack: string to be searched
* @needle: the substring to find in from
* Return: address of next characteristic of haystack or NULL
*/
char *starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}
/**
* _strcat - concatenates two strings and joinder
* @dest: destination buffer into
* @src: the source buffer from
* Return: pointer pointing towards destination buffer
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
