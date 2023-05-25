#include "shell.h"
/**
* chain_checker - chain delimeter buffer inspect
* @info: the index struct
* @buf: buffer char
* @p: buf location
*
* Return: 1 if chain delimeter, 0 if else
*/
int chain_checker(info_t *info, char *buf, size_t *p)
{
size_t j = *p;
if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = 0;
j++;
info->cmd_buf_type = CMD_OR;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
info->cmd_buf_type = CMD_AND;
}
else if (buf[j] == ';')
{
buf[j] = 0;
info->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*p = j;
return (1);
}
/**
* check_chain - inspect we should continue chaining based on last status
* @info: the framework struct
* @buf: buffer char
* @p: position in buf current location
* @i: buf starting location
* @len: buf lengh
*
* Return: Void
*/
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;
if (info->cmd_buf_type == CMD_AND)
{
if (info->status)
{
buf[i] = 0;
j = len;
}
}
if (info->cmd_buf_type == CMD_OR)
{
if (!info->status)
{
buf[i] = 0;
j = len;
}
}
*p = j;
}
/**
* alias_replacement - tokenized string alias_replacement
* @info: the parameter struct
*
* Return: 1 on success, 0 if else
*/
int alias_replacement(info_t *info)
{
int i;
record_m *node;
char *p;
for (i = 0; i < 10; i++)
{
node = node_starts_with(info->alias, info->argv[0], '=');
if (!node)
return (0);
free(info->argv[0]);
p = _strchr(node->str, '=');
if (!p)
return (0);
p = _strdup(p + 1);
if (!p)
return (0);
info->argv[0] = p;
}
return (1);
}
/**
* replace_vars - tokenized string vars replacement
* @info: framework struct
*
* Return: 1 on success , 0 if else
*/
int replace_vars(info_t *info)
{
int i = 0;
record_m *node;
for (i = 0; info->argv[i]; i++)
{
if (info->argv[i][0] != '$' || !info->argv[i][1])
continue;
if (!strcmp_char(info->argv[i], "$?"))
{
string_replacement(&(info->argv[i]),
_strdup(convert_number(info->status, 10, 0)));
continue;
}
if (!strcmp_char(info->argv[i], "$$"))
{
string_replacement(&(info->argv[i]),
_strdup(convert_number(getpid(), 10, 0)));
continue;
}
node = node_starts_with(info->env, &info->argv[i][1], '=');
if (node)
{
string_replacement(&(info->argv[i]),
_strdup(_strchr(node->str, '=') + 1));
continue;
}
string_replacement(&info->argv[i], _strdup(""));
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
