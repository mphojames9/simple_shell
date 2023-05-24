#include "shell.h"
/**
* chain_checks - confim if current character in buffer is a chain-delim
* @info: parameter structural
* @buf: character buffer
* @p: address of current position in buffer area
* Return: 1 if chain delimeter is observed, then if not 0
*/
int chain_checks(info_t *info, char *buf, size_t *p)
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
else if (buf[j] == ';') /* found ending of command */
{
buf[j] = 0; /* replace semicolon as null */
info->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*p = j;
return (1);
}
/**
* chain_inspect - checks  for continueationhaining based on last chek
* @info: parameter structural
* @buf: character  buffer
* @p: current position adsdress  in buf
* @i: starting point in buffer
* @len: length of the buffer
* Return: Void
*/
void chain_inspect(info_t *info, char *buf, size_t *p, size_t i, size_t len)
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
* alias_replacement - change alias in the tokenized string
* @info: parameter structural
* Return: 1 if replacement successfully, then if not 0
*/
int alias_replacement(info_t *info)
{
int i;
list_t *node;
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
* vars_replacement - replacement for vars in the tokenized string
* @info: parameter structural
* Return: 1 if replaced successfully, then if not 0
*/
int vars_replacement(info_t *info)
{
int i = 0;
list_t *node;
for (i = 0; info->argv[i]; i++)
{
if (info->argv[i][0] != '$' || !info->argv[i][1])
continue;
if (!strcmp_lexicogarphic(info->argv[i], "$?"))
{
string_replacement(&(info->argv[i]),
_strdup(convert_number(info->status, 10, 0)));
continue;
}
if (!strcmp_lexicogarphic(info->argv[i], "$$"))
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
* string_replacement - changes hte string
* @old: address position of old string
* @new: new string locational
* Return: 1 if replaced successfully, then if not 0
*/
int string_replacement(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
