#include "shell.h"
/**
* _memset - filling memory using constant byte
* @s: pointer pointing towards memory area
* @b: byte required for filling *s
* @n: quantity of bytes for filled state
* Return: (s) pointer pointing towards the memory area s
*/
char *_memset(char *s, char b, unsigned int n)
{
unsigned int i;
for (i = 0; i < n; i++)
s[i] = b;
return (s);
}
/**
* ffree - set free a string of strings
* @pp: the term string of strings
*/
void ffree(char **pp)
{
char **a = pp;
if (!pp)
return;
while (*pp)
free(*pp++);
free(a);
}
/**
* _realloc - reallocator for block of memory
* @ptr: pointer towards previous mallocated block
* @old_size: byte size for the previous block
* @new_size: byte size for the new block
* Return: pointer toward thee ol-block
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *p;
if (!ptr)
return (malloc(new_size));
if (!new_size)
return (free(ptr), NULL);
if (new_size == old_size)
return (ptr);
p = malloc(new_size);
if (!p)
return (NULL);
old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
p[old_size] = ((char *)ptr)[old_size];
free(ptr);
return (p);
}

