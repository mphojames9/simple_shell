#include "shell.h"
/**
* interactive_inspect - if the shell is in interactive_inspect mode return true
*
* @info: location of a struct
*
* Return: 1 will be retured if interactive_inspect mode is true, 0 if else
*/
int interactive_inspect(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
* delim_check - it will check if the shell is delimeter
*
* @c: checks the charecter to charecter
* @delim: string of the delimeter
* Return: 1 will be returned if if true and 0 if false
*/
int delim_check(char c, char *delim)
{
while (*delim)
if (*delim++ == c)
return (1);
return (0);
}
/**
* isalpha_inspect - alphabetic character will inspect
*
* @c: charactet to use or inset/put
*
* Return: 1 if true, 0 if else
*/
int isalpha_inspect(int c)
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
return (1);
else
return (0);
}
/**
* inspect_atoi - a string will be converted to an integer
*
* @s: coverted string
*
* Return: 0 if no numbers found in the string, converted
* number if numbers are found
*/
int inspect_atoi(char *s)
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

