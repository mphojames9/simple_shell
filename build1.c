#include "shell.h"
/**
* history_checker - views past events
* @info: Structure with possible clash
* Return: Always 0 when successful
*/
int history_checker(info_t *info)
{
print_list(info->history);
return (0);
}
/**
* unset_alias - stringed with another name
* @info: format
* @str: another name for the string
*
* Return: Always 0 on successful completion, 1 on error returned
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
ret = node_at_index_deletion(&(info->alias),
get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
*p = c;
return (ret);
}
/**
* set_alias - give a another name to the 
* @info: format
* @str: naming in another format
*
* Return: Always 0 on success, 1 on error
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
* print_alias - out screen sho of the string
* @node: node
*
* Return: Always 0 on successful completion, 1 if not
*/
int print_alias(record_m *node)
{
char *p = NULL, *a = NULL;
if (node)
{
p = _strchr(node->str, '=');
for (a = node->str; a <= p; a++)
putchar_char(*a);
putchar_char('\'');
_puts(p + 1);
_puts("'\n");
return (0);
}
return (1);
}
/**
* alias_checker - checker for the other names
* @info: possible clash
* Return: Always 0 for success
*/
int alias_checker(info_t *info)
{
int i = 0;
char *p = NULL;
record_m *node = NULL;
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

