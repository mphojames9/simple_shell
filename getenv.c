#include "shell.h"
/**
* get_environ - givees the string array copy for the environment
* @info: Structure with possibility of difference
* Return: Always 0 if true
*/
char **get_environ(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = to_the_strings_lister(info->env);
info->env_changed = 0;
}
return (info->environ);
}
/**
* deenv_setter - deletes environment variable
* @info: Structure with possible difference
* Return: 1 when deleted, then 0 otherwise if not
* @var: stringed environment variable property
*/
int deenv_setter(info_t *info, char *var)
{
list_t *node = info->env;
size_t i = 0;
char *p;
if (!node || !var)
return (0);
while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
info->env_changed = delete_node_at_index(&(info->env), i);
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
* env_setter - start a new environment var or change existing
* @info: Structure with possible clash
* @var: environmental variable charecteristics
* @value: environmental variable value for stringg
* Return: Always 0 if true and valid
*/
int env_setter(info_t *info, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *p;
if (!var || !value)
return (0);
buf = malloc(strlen_length(var) + strlen_length(value) + 2);
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
