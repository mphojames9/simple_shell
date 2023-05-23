#include "shell.h"
/**
* *_strncpy - copies string
* @dest: the destination string copy into
* @src: the source string string
* @n: the quantity of characters to be copied
* Return: concatenated string
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
* *_strncat - joins two strings
* @dest: first beginning string
* @src: the second next string
* @n: the quantity of bytes to be maximally used
* Return: the concatenated string
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
* *_strchr - finds character in a string
* @s: string to be parsed parsed
* @c: character to find
* Return: (s) this points to the memory area - s
*/
char *_strchr(char *s, char c)
{
do {
if (*s == c)
return (s);
} while (*s++ != '\0');
return (NULL);
}
