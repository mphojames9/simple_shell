#include "shell.h"
/**
* clear_info - starts the format
* @info: addressed structured
*/
void clear_info(particular_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}
/**
* set_info - starts format
* @info: addressed structured
* @av: vectored in argument
*/
void set_info(particular_t *info, char **av)
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
alias_replacement(info);
replace_vars(info);
}
}
/**
* free_info - makes spaced format
* @info: addressed structure
* @all: true if freed fields as whole
*/
void free_info(particular_t *info, int all)
{
ffree(info->argv);
info->argv = NULL;
info->path = NULL;
if (all)
{
if (!info->cmd_buf)
free(info->arg);
if (info->env)
untenanted_record(&(info->env));
if (info->history)
untenanted_record(&(info->history));
if (info->alias)
untenanted_record(&(info->alias));
ffree(info->environ);
info->environ = NULL;
befree((void **)info->cmd_buf);
if (info->readfd > 2)
close(info->readfd);
putchar_char(BUF_FLUSH);
}
}

