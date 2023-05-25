#include "shell.h"
/**
* env_checker - gets the environment as at now
* @info: format
* Return: Always 0 if valid
*/
int env_checker(particular_t *info)
{
print_list_str(info->env);
return (0);
}
/**
* _getenv - value of an environmental variable is gotten
* @info: format
* @name: named environmental variable
*
* Return: the value as at when valid
*/
char *_getenv(particular_t *info, const char *name)
{
record_m *node = info->env;
char *p;
while (node)
{
p = starts_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}
/**
* setenv_checker - get the environmental variable or change previous
* @info: format
* Return: Always 0 as at when valid
*/
int setenv_checker(particular_t *info)
{
if (info->argc != 3)
{
_eputs("Incorrect numberer of arguments\n");
return (1);
}
if (setenv2_checker(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}
/**
* unsetenv_checker - deletes environment variable
* @info: format
* Return: Always 0 if valid
*/
int unsetenv_checker(particular_t *info)
{
int i;
if (info->argc == 1)
{
_eputs("Too few arguements.\n");
return (1);
}
for (i = 1; i <= info->argc; i++)
unsetenv2_checker(info, info->argv[i]);
return (0);
}
/**
* env_list_population - populates environmental linked-list
* @info: format
* Return: Always 0 if valid
*/
int env_list_population(particular_t *info)
{
record_m *node = NULL;
size_t i;
for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
info->env = node;
return (0);
}
