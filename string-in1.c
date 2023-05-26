#include "shell.h"
/**
* _strcpy - string copy
*
* @dest: destination
* @src: source
*
* Return: destination pointer
*/
char *_strcpy(char *dest, char *src)
{
int i = 0;
if (dest == src || src == 0)
return (dest);
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = 0;
return (dest);
}
/**
* _strdup - string duplicates
*
* @str: duplicated string
*
* Return: duplicated string pointer
*/
char *_strdup(const char *str)
{
int length = 0;
char *ret;
if (str == NULL)
return (NULL);
while (*str++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;
return (ret);
}
/**
* _puts - input string printer
* @str: string printed
*
* Return: Nothing
*/
void _puts(char *str)
{
int i = 0;
if (!str)
return;
while (str[i] != '\0')
{
putchar_char(str[i]);
i++;
}
}
/**
* putchar_char - character c to stdout to be written
*
* @c: print character
*
* Return: 1 on success.
* On error, -1 is returned
*/
int putchar_char(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}
