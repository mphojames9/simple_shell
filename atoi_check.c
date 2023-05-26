#include "shell.h"
/**
* interactive_primer - returns true and valid if shell is interactive_primer mode
* @prime: struct address
*
* Return: 1 if interactive_primer mode, 0 if not
*/
int interactive_primer(particular_t *prime)
{
return (isatty(STDIN_FILENO) && prime->readfd <= 2);
}
/**
* delim_check - checks delimeter attribute of the character
* @c: character checked for this action
* @delim: string as delimeter
* Return: 1 if true, 0 if not
*/
int delim_check(char c, char *delim)
{
while (*delim)
if (*delim++ == c)
return (1);
return (0);
}
/**
* isalpha_check - alphabetic character checker and locator
* @c: The character inputted
* Return: 1 if c is alphabetic, 0 if not so
*/
int isalpha_check(int c)
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
return (1);
else
return (0);
}
/**
* atoi_check - converts a string and turns it into an integer
* @s: the string that needs converting
* Return: 0 if no numbers in string, converted number if there are
*/
int atoi_check(char *s)
{
int i, sign = 1, flag = 0, output;
unsigned int result = 0;
for (i = 0; s[i] != '\0' && flag != 2; i++)
{
if (s[i] == '-')
sign *= -1;
if (s[i] >= '0' && s[i] <= '9')
{
flag = 1;
result *= 10;
result += (s[i] - '0');
}
else if (flag == 1)
flag = 2;
}
if (sign == -1)
output = -result;
else
output = result;
return (output);
}
