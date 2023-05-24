#include "shell.h"
/**
* errational - changes string to integer
* @s: string to convert
* Return: 0 if there are no numbers in string,
* if not then return converted number
* if there is error return -1
*/
int errational(char *s)
{
int i = 0;
unsigned long int result = 0;
if (*s == '+')
s++; /* TODO: why does this instil main return 255? */
for (i = 0; s[i] != '\0'; i++)
{
if (s[i] >= '0' && s[i] <= '9')
{
result *= 10;
result += (s[i] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
}
return (result);
}
/**
* error_printer - prints message for error
* @info: the format and returning info structure
* @estr: string containingg error type
* Return: 0 when there aren't numbers in string,
* converted number if there are
* when there is error -1
*/
void error_printer(info_t *info, char *estr)
{
eputs_voider(info->fname);
eputs_voider(": ");
direct_print(info->line_count, STDERR_FILENO);
eputs_voider(": ");
eputs_voider(info->argv[0]);
eputs_voider(": ");
eputs_voider(estr);
}
/**
* direct_print - this prints an integer number in base 10
* @input: the inputed inputt
* @fd: the file-descriptor written into
* Return: number of characters on print
*/
int direct_print(int input, int fd)
{
int (*putchar)(char) = putchar_intiger;
int i, count = 0;
unsigned int _abs_, current;
if (fd == STDERR_FILENO)
putchar = eputchar_intiger;
if (input < 0)
{
_abs_ = -input;
putchar('-');
count++;
}
else
_abs_ = input;
current = _abs_;
for (i = 1000000000; i > 1; i /= 10)
{
if (_abs_ / i)
{
putchar('0' + current / i);
count++;
}
current %= i;
}
putchar('0' + current);
count++;
return (count);
}
/**
* convert_number - function to convert and get clone of itoa
* @num: number numb
* @base: base base
* @flags: argumenting flags
* Return: string stringing
*/
char *convert_number(long int num, int base, int flags)
{
static char *array;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = num;
if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';
}
array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" :
"0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';
do {
*--ptr = array[n % base];
n /= base;
} while (n != 0);
if (sign)
*--ptr = sign;
return (ptr);
}
/**
* comments_remover - fxn changes first instance of '#' with '\0'
* @buf: address of the string for modification
* Return: Always 0 if true;
*/
void comments_remover(char *buf)
{
int i;
for (i = 0; buf[i] != '\0'; i++)
if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
buf[i] = '\0';
break;
}
}
