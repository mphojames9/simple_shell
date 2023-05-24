#include "shell.h"
/**
* clear_info - initializes info_t struct
* @info: struct address
*/
void clear_info(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}
/**
* free_info - frees info_t struct fields
* @info: struct address
* @all: true if freeing all fields
*/
void free_info(info_t *info, int all)
{
ffree(info->argv);
info->argv = NULL;
info->path = NULL;
if (all)
{
if (!info->cmd_buf)
free(info->arg);
if (info->env)
free_list(&(info->env));
if (info->history)
free_list(&(info->history));
if (info->alias)
free_list(&(info->alias));
ffree(info->environ);
info->environ = NULL;
befree((void **)info->cmd_buf);
if (info->readfd > 2)
close(info->readfd);
putchar_char(BUF_FLUSH);
}
}
<<<<<<< HEAD


=======
>>>>>>> 3e606b195c52ac6a1de82fadd1099acb88169adc
