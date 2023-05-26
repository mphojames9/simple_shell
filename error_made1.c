#include "shell.h"
/**
* erratoi_check - changes string to integerr
* @s: string for to be converted
* Return: 0 if no there are no numbers in string if not convert the number
* -1 on error given
*/
int erratoi_check(char *s)
{
int i = 0;
unsigned long int result = 0;
if (*s == '+')
s++;
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
* print_error - error message notificator
* @prime: format and return form
* @estr: string containing type error specificity
* Return: 0 if no numbers found in string if not then convert the number
* -1 on error given
*/
void print_error(particular_t *prime, char *estr)
{
_eputs(prime->fname);
_eputs(": ");
printing_d(prime->rule_count, STDERR_FILENO);
_eputs(": ");
_eputs(prime->argv[0]);
_eputs(": ");
_eputs(estr);
}
/**
* printing_d - function prints a decimal number-base 10
* @input: the inputted value
* @fd: file-descriptor to write into
*
* Return: number of characters as printed
*/
int printing_d(int input, int fd)
{
int (*_putchar_char)(char) = putchar_char;
int i, count = 0;
unsigned int _abs_, current;
if (fd == STDERR_FILENO)
_putchar_char = eputchar_chr;
if (input < 0)
{
_abs_ = -input;
_putchar_char('-');
count++;
}
else
_abs_ = input;
current = _abs_;
for (i = 1000000000; i > 1; i /= 10)
{
if (_abs_ / i)
{
_putchar_char('0' + current / i);
count++;
}
current %= i;
}
_putchar_char('0' + current);
count++;
return (count);
}
/**
* convert_number - converterting function
* @number: number-
* @base: base-
* @flags: argument flags-
*
* Return: string str-
*/
char *convert_number(long int number, int base, int flags)
{
static char *array;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = number;
if (!(flags & CONVERT_UNSIGNED) && number < 0)
{
n = -number;
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
* remove_comments - this function replaces the first
* instance occurence of '#' with '\0'
* @buf: address of the string for modification
*
* Return: Always 0 when valid;
*/
void remove_comments(char *buf)
{
int i;
for (i = 0; buf[i] != '\0'; i++)
if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
buf[i] = '\0';
break;
}
}
