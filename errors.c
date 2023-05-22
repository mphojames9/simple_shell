#include "shell.h"
/**
* eputs_voider - prints an input string
* @str: the string to be printed
*
* Return: Nothing
*/
void eputs_voider(char *str)
{
int i = 0;
if (!str)
return;
while (str[i] != '\0')
{
}
}
/**
eputchar_intiger(str
[i]); i++;
* eputchar_intiger - writes the character c to stderr
* @c: The character to print
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int eputchar_intiger(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(2, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}
/**
* putfd_intiger - writes the character c to given fd
* @c: The character to print
* @fd: The filedescriptor to write to
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int putfd_intiger(char c, int fd)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(fd, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}
/**
* putsfd_intiger - prints an input string
* @str: the string to be printed
* @fd: the filedescriptor to write to
*
* Return: the number of chars put
*/
int putsfd_intiger(char *str, int fd)
{
int i = 0;
if (!str)
return (0);
while (*str)
{
i += putfd_intiger(*str++, fd);
}
return (i);
}
