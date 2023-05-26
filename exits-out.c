#include "shell.h"
/**
**_strncpy - duplicates string
*@dest: destination string copied into
*@src: source-string
*@n: amount of characters for copying
*Return: concatenated string form
*/
char *_strncpy(char *dest, char *src, int n)
{
int i, j;
char *s = dest;
i = 0;
while (src[i] != '\0' && i < n - 1)
{
dest[i] = src[i];
i++;
}
if (i < n)
{
j = i;
while (j < n)
{
dest[j] = '\0';
j++;
}
}
return (s);
}
/**
**_strncat - concatenates two-strings
*@dest: the first-string
*@src: the second-string
*@n: quantity of bytes to be maximally used
*Return: the concatenated string as given
*/
char *_strncat(char *dest, char *src, int n)
{
int i, j;
char *s = dest;
i = 0;
j = 0;
while (dest[i] != '\0')
i++;
while (src[j] != '\0' && j < n)
{
dest[i] = src[j];
i++;
j++;
}
if (j < n)
dest[i] = '\0';
return (s);
}
/**
**_strchr - locates character in string
*@s: string to be parsed parsee
*@c: character to look out for
*Return: (s) a pointer to the memory area s as given
*/
char *_strchr(char *s, char c)
{
do {
if (*s == c)
return (s);
} while (*s++ != '\0');
return (NULL);
}
