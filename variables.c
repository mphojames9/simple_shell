#include "shell.h"
/**
* chain_checker - chain delimeter buffer inspect
* @prime: the index struct
* @buf: buffer char
* @p: buf location
*
* Return: 1 if chain delimeter, 0 if else
*/
int chain_checker(particular_t *prime, char *buf, size_t *p)
{
size_t j = *p;
if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = 0;
j++;
prime->cmd_buf_type = CMD_OR;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
prime->cmd_buf_type = CMD_AND;
}
else if (buf[j] == ';')
{
buf[j] = 0;
prime->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*p = j;
return (1);
}
/**
* check_chain - inspect we should continue chaining based on last status
* @prime: the framework struct
* @buf: buffer char
* @p: position in buf current location
* @i: buf starting location
* @len: buf lengh
*
* Return: Void
*/
void check_chain(particular_t *prime, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;
if (prime->cmd_buf_type == CMD_AND)
{
if (prime->status)
{
buf[i] = 0;
j = len;
}
}
if (prime->cmd_buf_type == CMD_OR)
{
if (!prime->status)
{
buf[i] = 0;
j = len;
}
}
*p = j;
}
/**
* alias_replacement - tokenized string alias_replacement
* @prime: the parameter struct
*
* Return: 1 on success, 0 if else
*/
int alias_replacement(particular_t *prime)
{
int i;
record_m *node;
char *p;
for (i = 0; i < 10; i++)
{
node = node_starts_with(prime->alias, prime->argv[0], '=');
if (!node)
return (0);
free(prime->argv[0]);
p = _strchr(node->str, '=');
if (!p)
return (0);
p = _strdup(p + 1);
if (!p)
return (0);
prime->argv[0] = p;
}
return (1);
}
/**
* replace_vars - tokenized string vars replacement
* @prime: framework struct
*
* Return: 1 on success , 0 if else
*/
int replace_vars(particular_t *prime)
{
int i = 0;
record_m *node;
for (i = 0; prime->argv[i]; i++)
{
if (prime->argv[i][0] != '$' || !prime->argv[i][1])
continue;
if (!strcmp_char(prime->argv[i], "$?"))
{
string_replacement(&(prime->argv[i]),
_strdup(convert_number(prime->status, 10, 0)));
continue;
}
if (!strcmp_char(prime->argv[i], "$$"))
{
string_replacement(&(prime->argv[i]),
_strdup(convert_number(getpid(), 10, 0)));
continue;
}
node = node_starts_with(prime->env, &prime->argv[i][1], '=');
if (node)
{
string_replacement(&(prime->argv[i]),
_strdup(_strchr(node->str, '=') + 1));
continue;
}
string_replacement(&prime->argv[i], _strdup(""));
}
return (0);
}
/**
* string_replacement - string replacement
* @old: old string location
* @new: new string
*
* Return: return 1 on success, 0 if fails
*/
int string_replacement(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
