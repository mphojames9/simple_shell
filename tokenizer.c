#include "shell.h"
/**
* **strtow - splits a string into words
* @str: inputted string
* @d: delimetered string
* Return: pointer pointing to an array of strings, or NULL on fail
*/
char **strtow(char *str, char *d)
{
int i, j, k, m, numericwords = 0;
char **s;
if (str == NULL || str[0] == 0)
return (NULL);
if (!d)
d = " ";
for (i = 0; str[i] != '\0'; i++)
if (!delim_check(str[i], d) && (delim_check(str[i + 1], d) || !str[i + 1]))
numericwords++;
if (numericwords == 0)
return (NULL);
s = malloc((1 + numericwords)*sizeof(char *));
if (!s)
return (NULL);
for (i = 0, j = 0; j < numericwords; j++)
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
* **strtow2 - splits string form to words
* @str: inputted string
* @d: delimetered
* Return: pointer pointing toward an array of strings, or NULL on fail
*/
char **strtow2(char *str, char d)
{
int i, j, k, m, numericwords = 0;
char **s;
if (str == NULL || str[0] == 0)
return (NULL);
for (i = 0; str[i] != '\0'; i++)
if ((str[i] != d && str[i + 1] == d) ||
(str[i] != d && !str[i + 1]) || str[i + 1] == d)
numericwords++;
if (numericwords == 0)
return (NULL);
s = malloc((1 + numericwords)*sizeof(char *));
if (!s)
return (NULL);
for (i = 0, j = 0; j < numericwords; j++)
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
}
for (m = 0; m < k; m++)
s[j][m] = str[i++];
s[j][m] = 0;
}
s[j] = NULL;
return (s);
}
