#include "shell.h"
/**
* _memset - memory with a constant byte filler
*
* @s: pointer to the memory location
* @b: the byte to fill *s 
* @n: to be filled with amount of byte
* Return: memory area s
*/
char *_memset(char *s, char b, unsigned int n)
{
unsigned int i;
for (i = 0; i < n; i++)
s[i] = b;
return (s);
}
/**
* ffree - frees a string
* @pp: string of strings
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
* _realloc - block of memory
* @ptr: previous malloc'ated block pointer
*
* @old_size: previous block byte size
* @new_size: new block byte size
*
* Return: ol'block nameen.
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
