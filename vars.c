#include "shell.h"
/**
* chain_checker - test if current char in buffer is a chain delimeter
* @info: the parameter struct
* @buf: the char buffer
* @p: address of current position in buf
*
* Return: 1 if chain delimeter, 0 otherwise
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
else if (buf[j] == ';') /* found end of this command */
{
buf[j] = 0; /* replace semicolon with null */
info->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*p = j;
return (1);
}
/**
* check_chain - checks we should continue chaining based on last status
* @info: the parameter struct
* @buf: the char buffer
* @p: address of current position in buf
* @i: starting position in buf
* @len: length of buf
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
* alias_replacement - replaces an aliases in the tokenized string
* @info: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
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
* replace_vars - replaces vars in the tokenized string
* @info: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
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
int string_replacement(char **, char *)
{
return 0;
}
/**
 * string_replacement - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int string_replacement(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
