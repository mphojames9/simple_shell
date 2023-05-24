#include "shell.h"
/**
* _strcpy - copies string sttring
* @dest: destination to go
* @src: source source
* Return: pointer pointing toward destination
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
* _strdup - duplicates copy string
* @str: the string to  be duplicated
* Return: pointer for  duplicated string
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
* _puts - prints out input string string
* @str: the string for  printed version
* Return: Nothing at all
*/
void _puts(char *str)
{
int i = 0;
if (!str)
return;
while (str[i] != '\0')
{
putchar_intiger(str[i]);
i++;
}
}
/**
* putchar_intiger - writes the char c to std-out
* @c: character to be printed out
* Return: On successful 1.
* On error, -1 is returned when fail, and errno is given valid
*/
int putchar_intiger(char c)
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
