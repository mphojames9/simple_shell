#include "shell.h"
/**
* _myevacuate - leaves shell
* @info: Structure with possible clash
* Return: exit as an exited stat
* (0) if info.argv[0] != "exit"
*/
int _myevacuate(particular_t *info)
{
int exitcheck;
if (info->argv[1])
{
exitcheck = erratoi_check(info->argv[1]);
if (exitcheck == -1)
{
info->status = 2;
print_error(info, "Illegal number: ");
_eputs(info->argv[1]);
eputchar_chr('\n');
return (1);
}
info->err_num = erratoi_check(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}
/**
* cd_change - gets the current directory into another
* @info: Structure with possible clash
* Return: Always 0 when successful
*/
int cd_change(particular_t *info)
{
char *s, *dir, buffer[1024];
int chdir_ret;
s = getcwd(buffer, 1024);
if (!s)
_puts("TODO: >>getcwd failure-msg here<<\n");
if (!info->argv[1])
{
dir = _getenv(info, "HOME=");
if (!dir)
chdir_ret = /* TODO: what should this as refer be? */
chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (strcmp_char(info->argv[1], "-") == 0)
{
if (!_getenv(info, "OLDPWD="))
{
_puts(s);
putchar_char('\n');
return (1);
}
_puts(_getenv(info, "OLDPWD=")), putchar_char('\n');
chdir_ret = /* TODO: what should this be? */
chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(info->argv[1]);
if (chdir_ret == -1)
{
print_error(info, "can't cd to ");
_eputs(info->argv[1]), eputchar_chr('\n');
}
else
{
setenv2_checker(info, "OLDPWD", _getenv(info, "PWD="));
setenv2_checker(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}
/**
* _myassistance - reshuffle the working directory
* @info: Structure with possible clash
* Return: Always 0 if successful completed
*/
int _myassistance(particular_t *info)
{
char **arg_array;
arg_array = info->argv;
_puts("help call works. Function not implemented \n");
if (0)
_puts(*arg_array);
return (0);
}
