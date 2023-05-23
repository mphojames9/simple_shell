#include "shell.h"
/**
* hsh_int - main shell loop
* @info: the parameter & return info struct
* @av: the argument vector from main()
*
* Return: 0 on success, 1 on error, or error code
*/
int hsh_int(info_t *info, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;
while (r != -1 && builtin_ret != -2)
{
information_clearing(info);
if (interactive_inspect(info))
_puts("$ ");
eputchar_intiger(BUF_FLUSH); r = get_input(info);
if (r != -1)
{
informantion_setting(info, av);
builtin_ret =
builtin_finder(info);
if
(builtin_ret == -1)
find_cmd(info);
}
else if (interactive_inspect(info))putchar_intiger('\n');
information_freeing(info, 0);
}
history_writer(info);
information_freeing(info, 1);
if (!interactive_inspect(info) && info->status) exit(info->status);
if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_ret);
}
/**
* builtin_finder - finds a builtin command
* @info: the parameter & return info struct
*
* Return: -1 if builtin not found,
* 0 if builtin executed successfully,
* 1 if builtin found but not successful,
* 2 if builtin signals exit()
*/
int builtin_finder(info_t *info)
{
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", my_evacuation},
{"env", environ_checker},
{"help", _assist},
{"history", _myhistory},
{"setenv", selfenv_setter},
{"unsetenv", selfdeenv_setter},
{"cd", directory_change},
{"alias", _myalias},
{NULL, NULL}
};
for (i = 0; builtintbl[i].type; i++)
if (strcmp_lexicogarphic(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
built_in_ret = builtintbl[i].func(info);
break;
}
return (built_in_ret);
}
/**
* find_cmd - finds a command in PATH
* @info: the parameter & return info struct
*
* Return: void
*/
void find_cmd(info_t *info)
{
char *path = NULL;
int i, k;
info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
for (i = 0, k = 0; info->arg[i]; i++)
if (!delim_check(info->arg[i], "\t\n")) k++;
if (!k)
return;
path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
if (path)
{
}
else
{
info->path = path;
fork_cmd(info);
if ((interactive_inspect(info) || _getenv(info, "PATH=")
|| info->argv[0][0] == '/') && cmd_checker(info, info->argv[0])) fork_cmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
error_printer(info, "not found\n");
}
}
}
/**
* fork_cmd - forks a an exec thread to run cmd
* @info: the parameter & return info struct
*
* Return: void
*/
void fork_cmd(info_t *info)
{
pid_t child_pid;
child_pid = fork();
if (child_pid == -1)
{
/* TODO: PUT ERROR FUNCTION */
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, get_environ(info)) == -1)
{
information_freeing(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
/* TODO: PUT ERROR FUNCTION */
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
error_printer(info, "Permission denied\n");
}
}
}

