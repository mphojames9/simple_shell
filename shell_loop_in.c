#include "shell.h"
/**
* hsh - shell loop
*
* @info: treturn info struct
* @av: vector from main disagreement
*
* Return: 0 on success, 1 on error
*/
int hsh(particular_t *info, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;
while (r != -1 && builtin_ret != -2)
{
clear_info(info);
if (interactive_infor(info))
_puts("$ ");
eputchar_chr(BUF_FLUSH);
r = get_input(info);
if (r != -1)
{
set_info(info, av);
builtin_ret = builtin_locator(info);
if (builtin_ret == -1)
find_cmd(info);
}
else if (interactive_infor(info))
putchar_char('\n');
free_info(info, 0);
}
history_writer(info);
free_info(info, 1);
if (!interactive_infor(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_ret);
}
/**
* builtin_locator - builtin command finder
*
* @info: parameter & info struct
*
* Return: -1 if builtin not found,
* 0 if builtin executed successfully,
* 1 if builtin found but not successful,
* 2 if builtin signals exit()
*/
int builtin_locator(particular_t *info)
{
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", _myevacuate},
{"env", env_checker},
{"help", _myassistance},
{"history", history_checker},
{"setenv", setenv_checker},
{"unsetenv", unsetenv_checker},
{"cd", cd_change},
{"alias", alias_checker},
{NULL, NULL}
};
for (i = 0; builtintbl[i].type; i++)
if (strcmp_char(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
built_in_ret = builtintbl[i].func(info);
break;
}
return (built_in_ret);
}
/**
* find_cmd - command in PATH finder
* @info: the parameter index
*
* Return: void
*/
void find_cmd(particular_t *info)
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
if (!delim_check(info->arg[i], " \t\n"))
k++;
if (!k)
return;
path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
fork_cmd(info);
}
else
{
if ((interactive_infor(info) || _getenv(info, "PATH=")
|| info->argv[0][0] == '/') && cmd_checker(info, info->argv[0]))
fork_cmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
print_error(info, "not found\n");
}
}
}
/**
* fork_cmd - thread to run cmd forker
*
* @info: the parameter
*
* Return: void
*/
void fork_cmd(particular_t *info)
{
pid_t child_pid;
child_pid = fork();
if (child_pid == -1)
{

perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, get_environ(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}

}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_error(info, "Permission denied\n");
}
}
}
