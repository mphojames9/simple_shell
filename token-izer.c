#include "shell.h"
/**
* **strtow - string splits into word
*
* @str: string input
*
* @d: the delimeter string
* Return: array poiterstrings, or NULL on failure
*/
char **strtow(char *str, char *d)
{
int i, j, k, m, numberwords = 0;
char **s;
if (str == NULL || str[0] == 0)
return (NULL);
if (!d)
d = " ";
for (i = 0; str[i] != '\0'; i++)
if (!delim_check(str[i], d) && (delim_check(str[i + 1], d) || !str[i + 1]))
numberwords++;
if (numberwords == 0)
return (NULL);
s = malloc((1 + numberwords)*sizeof(char *));
if (!s)
return (NULL);
for (i = 0, j = 0; j < numberwords; j++)
{
while (delim_check(str[i], d))
i++;
k = 0;
while (!delim_check(str[i + k], d) && str[i + k])
k++;
s[j] = malloc((k + 1) * sizeof(char));
if (!s[j])
{
for (k = 0; k < j; k++)
free(s[k]);
free(s);
return (NULL);
}
for (m = 0; m < k; m++)
s[j][m] = str[i++];
s[j][m] = 0;
}
s[j] = NULL;
return (s);
}
/**
* **strtow2 - string splits into words
* @str: string input
* @d: delimeter
* Return: array poiter strings, or NULL on failure
*/
char **strtow2(char *str, char d)
{
int i, j, k, m, numberwords = 0;
char **s;
if (str == NULL || str[0] == 0)
return (NULL);
for (i = 0; str[i] != '\0'; i++)
if ((str[i] != d && str[i + 1] == d) ||
(str[i] != d && !str[i + 1]) || str[i + 1] == d)
numberwords++;
if (numberwords == 0)
return (NULL);
s = malloc((1 + numberwords)*sizeof(char *));
if (!s)
return (NULL);
for (i = 0, j = 0; j < numberwords; j++)
{
while (str[i] == d && str[i] != d)
i++;
k = 0;
while (str[i + k] != d && str[i + k] && str[i + k] != d)
k++;
s[j] = malloc((k + 1) * sizeof(char));
if (!s[j])
{
for (k = 0; k < j; k++)
free(s[k]);
free(s);
return (NULL);
} for (
m
=
0; m
<
k; m++)
s[j][m] = str[i++];
s[j][m] = 0;
}
s[j] = NULL;
return (s);
}
