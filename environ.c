#include "shell.h"
/**
* environ_checker - prints the current environment
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int environ_checker(info_t *info)
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
list_t *node = info->env;
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
* selfenv_setter - Initialize a new environment variable,
* or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int selfenv_setter(info_t *info)
{
if (info->argc != 3)
{
eputs_voider("Incorrect number ofarguements\n");
return (1);
}
if (env_setter(info,info->argv[1],info->argv[2]))
return (0);
return (1);
}
/**
* selfdeenv_setter - Remove an environment variable
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int selfdeenv_setter(info_t *info)
{
int i;
if (info->argc == 1)
{
eputs_voider("Too few arguements.\n");
return (1);
}
for (i = 1; i <= info->argc; i++)
deenv_setter(info, info->argv[i]);
return (0);
}
/**
* env_list_populator - populates env linked list
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int env_list_populator(info_t *info)
{
list_t *node = NULL;
size_t i;
for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
info->env = node;
return (0);
}

