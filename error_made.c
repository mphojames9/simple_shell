#include "shell.h"
/**
* _eputs - prints-out inputted string
* @str: printed string
* Return: Nothing at all
*/
void _eputs(char *str)
{
int i = 0;
if (!str)
return;
while (str[i] != '\0')
{
eputchar_chr(str[i]);
i++;
}
}
/**
* eputchar_chr - writes the character c to stANdarderror
* @c: character for printing
*
* Return: On success 1 if valid
* On error -1 is affirmative, and error-no is set as required
*/
int eputchar_chr(char c)
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
* putfd_char - writes character c to given file-descriptor
* @c: character for printing to
* @fd: file-descriptor to write into
*
* Return: On success 1 if valid
* On error -1 is affirmative, and error-no is set as required
*/
int putfd_char(char c, int fd)
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
* putsfd_char - input stringed printing
* @str: to be printed stringed
* @fd: file-descriptor to write into
*
* Return: nums of characters put
*/
int putsfd_char(char *str, int fd)
{
int i = 0;
if (!str)
return (0);
while (*str)
{
i += putfd_char(*str++, fd);
}
return (i);
}
