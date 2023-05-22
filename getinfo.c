#include "shell.h"
/**
* information_clearing - initializes info_t struct
* @info: struct address
*/
void information_clearing(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}
/**
* informantion_setting - initializes info_t struct
* @info: struct address
* @av: argument vector
*/
void informantion_setting(info_t *info, char **av)
{
int i = 0;
info->fname = av[0];
if (info->arg)
{
info->argv = strtow(info->arg, " \t");
if (!info->argv)
{
info->argv = malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = _strdup(info->arg);
info->argv[1] = NULL;
}
}
for (i = 0; info->argv && info->argv[i]; i++)
;
info->argc = i;
alias_replacement(info)
;
vars_replacement(info)
;
}
}
/**
* information_freeing - frees info_t struct fields
* @info: struct address
* @all: true if freeing all fields
*/
void information_freeing(info_t *info, int all)
{
_safer(info->argv);
info->argv = NULL;
info->path = NULL;
if (all)
{
if (!info->cmd_buf)
free(info->arg);
if (info->env)
list_freer(&(info->env));
if (info->history)
list_freer(&(info->history));
if (info->alias)
list_freer(&(info->alias));
_safer(info->environ);
info->environ = NULL;
bsafer((void **)info->cmd_buf);
if (info->readfd >2)
close(info->readfd);
putchar_intiger(BUF_FLUSH);
}
}
