#include "shell.h"
/**
* get_environ - environmental array getting
* @info: format
* Return: Always 0
*/
char **get_environ(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = record_mo_strings(info->env);
info->env_changed = 0;
}
return (info->environ);
}
/**
* unsetenv2_checker - deletes environment variable
* @info: format
* Return: 1 on sure delete, if not 0
* @var: environmental variable stringed property
*/
int unsetenv2_checker(info_t *info, char *var)
{
record_m *node = info->env;
size_t i = 0;
char *p;
if (!node || !var)
return (0);
while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
info->env_changed = node_at_index_deletion(&(info->env), i);
i = 0;
node = info->env;
continue;
}
node = node->next;
i++;
}
return (info->env_changed);
}
/**
* setenv2_checker - start a new variable or change previous
* @info: format
* @var: environmental variable stringed property
* @value: environmental variable stringed value
* Return: Always if true and valid 0
*/
int setenv2_checker(info_t *info, char *var, char *value)
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
node = info->env;
while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
info->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_end(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}
