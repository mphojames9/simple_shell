#include "shell.h"
/**
* get_environ - environmental array getting
* @prime: format
* Return: Always 0
*/
char **get_environ(particular_t *prime)
{
if (!prime->environ || prime->env_changed)
{
prime->environ = record_mo_strings(prime->env);
prime->env_changed = 0;
}
return (prime->environ);
}
/**
* unsetenv2_checker - deletes environment variable
* @prime: format
* Return: 1 on sure delete, if not 0
* @var: environmental variable stringed property
*/
int unsetenv2_checker(particular_t *prime, char *var)
{
record_m *node = prime->env;
size_t i = 0;
char *p;
if (!node || !var)
return (0);
while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
prime->env_changed = node_at_index_deletion(&(prime->env), i);
i = 0;
node = prime->env;
continue;
}
node = node->next;
i++;
}
return (prime->env_changed);
}
/**
* setenv2_checker - start a new variable or change previous
* @prime: format
* @var: environmental variable stringed property
* @value: environmental variable stringed value
* Return: Always if true and valid 0
*/
int setenv2_checker(particular_t *prime, char *var, char *value)
{
char *buf = NULL;
record_m *node;
char *p;
if (!var || !value)
return (0);
buf = malloc(strlen_char(var) + strlen_char(value) + 2);
if (!buf)
return (1);
_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);
node = prime->env;
while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
prime->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_end(&(prime->env), buf, 0);
free(buf);
prime->env_changed = 1;
return (0);
}
