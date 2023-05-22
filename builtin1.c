#include "shell.h"
/**
* _myhistory - show the history list, one command per line, start
* with line numbers, commencing at 0.
* @info: Structure containing the potential arguments
* Return: Always if true 0
*/
int _myhistory(info_t *info)
{
print_list(info->history);
return (0);
}
/**
* unset_alias - assign alias to string
* @info: parameter structure structure
* @str: the string assigned alias
* Return: Always 0 on successful, then 1 on error
*/
int unset_alias(info_t *info, char *str)
{
char *p, c;
int ret;
p = _strchr(str, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = delete_node_at_index(&(info->alias),
get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
*p = c;
return (ret);
}
/**
* set_alias - assigns alias to string
* @info: parameter structure
* @str: the string assigned alias
* Return: Always 0 on successful, then 1 on error
*/
int set_alias(info_t *info, char *str)
{
char *p;
p = _strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (unset_alias(info, str));
unset_alias(info, str);
return (add_node_end(&(info->alias), str, 0) == NULL);
}
/**
* print_alias - print out alias string
* @node: alias node node
* Return: Always if true 0 on success, then 1 on error
*/
int print_alias(list_t *node)
{
char *p = NULL, *a = NULL;
if (node)
{
p = _strchr(node->str, '=');
for (a = node->str; a <= p; a++)
putchar_intiger(*a);
putchar_intiger('\'');
_puts(p + 1);
_puts("'\n");
return (0);
}
return (1);
}
/**
* _myalias - copies characteristics of alias builtin - man alias
* @info: Structure containing the potential arguments
* Return: Always if true 0
*/
int _myalias(info_t *info)
{
int i = 0;
char *p = NULL;
list_t *node = NULL;
if (info->argc == 1)
{
node = info->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; info->argv[i]; i++)
{
p = _strchr(info->argv[i], '=');
if (p)
	set_alias(info, info->argv[i]);
else
print_alias(node_starts_with(info->alias, info->argv[i], '='));
}
return (0);
}
