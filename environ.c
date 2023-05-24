#include "shell.h"
/**
* env_checker - prints the current environment
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int env_checker(info_t *info)
{
print_list_str(info->env);
return (0);
}
/**
* _getenv - gets the value of an environ variable
* @info: Structure containing potential arguments. Used to maintain
* @name: env var name
*
* Return: the value
*/
char *_getenv(info_t *info, const char *name)
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
* setenv_checker - Initialize a new environment variable,
* or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int setenv_checker(info_t *info)
{
if (info->argc != 3)
{
_eputs("Incorrect number of arguements\n");
return (1);
}
if (setenv2_checker(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}
/**
* unsetenv_checker - Remove an environment variable
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int unsetenv_checker(info_t *info)
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
* env_list_population - populates env linked list
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int env_list_population(info_t *info)
{
record_m *node = NULL;
size_t i;
for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
info->env = node;
return (0);
}
