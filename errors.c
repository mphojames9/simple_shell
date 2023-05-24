#include "shell.h"
/**
* eputs_voider - prints input for string
* @str: string for printing
* Return: Nothing at all
*/
void eputs_voider(char *str)
{
int i = 0;
if (!str)
return;
while (str[i] != '\0')
{
eputchar_intiger(str[i]);
i++;
}
}
/**
* eputchar_intiger - prints character c to the stderror
* @c: character for printing
* Return: On successful complete 1.
* On error, -1, and errno is given valid
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
* putfd_intiger - priint character c specified for fd
* @c: character for printing
* @fd: file-descriptor writing into
* Return: On successful complete 1
* On error -1, and errorno is given valid
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
* putsfd_intiger - prints string input as necessary
* @str: string for printing
* @fd: file-descriptor for writing
* Return: the number of characters inputted
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
