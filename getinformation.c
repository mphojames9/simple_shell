#include "shell.h"
/**
* clear_prime - starts the format
* @prime: addressed structured
*/
void clear_prime(particular_t *prime)
{
prime->arg = NULL;
prime->argv = NULL;
prime->path = NULL;
prime->argc = 0;
}
/**
* set_prime - starts format
* @prime: addressed structured
* @av: vectored in argument
*/
void set_prime(particular_t *prime, char **av)
{
int i = 0;
prime->fname = av[0];
if (prime->arg)
{
prime->argv = strtow(prime->arg, " \t");
if (!prime->argv)
{
prime->argv = malloc(sizeof(char *) * 2);
if (prime->argv)
{
prime->argv[0] = _strdup(prime->arg);
prime->argv[1] = NULL;
}
}
for (i = 0; prime->argv && prime->argv[i]; i++)
;
prime->argc = i;
alias_replacement(prime);
replace_vars(prime);
}
}
/**
* free_prime - makes spaced format
* @prime: addressed structure
* @all: true if freed fields as whole
*/
void free_prime(particular_t *prime, int all)
{
ffree(prime->argv);
prime->argv = NULL;
prime->path = NULL;
if (all)
{
if (!prime->cmd_buf)
free(prime->arg);
if (prime->env)
untenanted_record(&(prime->env));
if (prime->history)
untenanted_record(&(prime->history));
if (prime->alias)
untenanted_record(&(prime->alias));
ffree(prime->environ);
prime->environ = NULL;
befree((void **)prime->cmd_buf);
if (prime->readfd > 2)
close(prime->readfd);
putchar_char(BUF_FLUSH);
}
}

