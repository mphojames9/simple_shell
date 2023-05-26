#include "shell.h"
/**
* env_checker - gets the environment as at now
* @prime: format
* Return: Always 0 if valid
*/
int env_checker(particular_t *prime)
{
print_list_str(prime->env);
return (0);
}
/**
* _getenv - value of an environmental variable is gotten
* @prime: format
* @name: named environmental variable
*
* Return: the value as at when valid
*/
char *_getenv(particular_t *prime, const char *name)
{
record_m *node = prime->env;
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
* @prime: format
* Return: Always 0 as at when valid
*/
int setenv_checker(particular_t *prime)
{
if (prime->argc != 3)
{
_eputs("Incorrect numberer of arguments\n");
return (1);
}
if (setenv2_checker(prime, prime->argv[1], prime->argv[2]))
return (0);
return (1);
}
/**
* unsetenv_checker - deletes environment variable
* @prime: format
* Return: Always 0 if valid
*/
int unsetenv_checker(particular_t *prime)
{
int i;
if (prime->argc == 1)
{
_eputs("Too few arguements.\n");
return (1);
}
for (i = 1; i <= prime->argc; i++)
unsetenv2_checker(prime, prime->argv[i]);
return (0);
}
/**
* env_list_population - populates environmental linked-list
* @prime: format
* Return: Always 0 if valid
*/
int env_list_population(particular_t *prime)
{
record_m *node = NULL;
size_t i;
for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
prime->env = node;
return (0);
}
