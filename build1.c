#include "shell.h"
/**
* history_checker - views past events
* @prime: Structure with possible clash
* Return: Always 0 when successful
*/
int history_checker(particular_t *prime)
{
print_list(prime->history);
return (0);
}
/**
* unset_alias - stringed with another name
* @prime: format
* @str: another name for the string
*
* Return: Always 0 on successful completion, 1 on error returned
*/
int unset_alias(particular_t *prime, char *str)
{
char *p, c;
int ret;
p = _strchr(str, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = node_at_index_deletion(&(prime->alias),
get_node_index(prime->alias, node_starts_with(prime->alias, str, -1)));
*p = c;
return (ret);
}
/**
* set_alias - give a another name to the
* @prime: format
* @str: naming in another format
*
* Return: Always 0 on success, 1 on error
*/
int set_alias(particular_t *prime, char *str)
{
char *p;
p = _strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (unset_alias(prime, str));
unset_alias(prime, str);
return (add_node_end(&(prime->alias), str, 0) == NULL);
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
* @prime: possible clash
* Return: Always 0 for success
*/
int alias_checker(particular_t *prime)
{
int i = 0;
char *p = NULL;
record_m *node = NULL;
if (prime->argc == 1)
{
node = prime->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; prime->argv[i]; i++)
{
p = _strchr(prime->argv[i], '=');
if (p)
set_alias(prime, prime->argv[i]);
else
print_alias(node_starts_with(prime->alias, prime->argv[i], '='));
}
return (0);
}

