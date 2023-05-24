#include "shell.h"
/**
* my_evacuation - shell evacuation
*
* @info: Structure having posible disagreement.
* Used to control constant function framework.
*
* Return: given status evacuation
* 0 when info.argv[0] != "exit"
*/
int my_evacuation(info_t *info)
{
int exitcheck;
if (info->argv[1])
{
exitcheck = errational(info->argv[1]);
if (exitcheck == -1)
{
info->status = 2;
error_printer(info, "unallowed intiger");
eputs_voider(info->argv[1]);
eputchar_intiger('\n');
return (1);
}
info->err_num = errational(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}
/**
* directory_change - the current directory will be
* changed on the process
*
* @info: Structure having posible disagreement.
* Used to control constant function framework.
*
* Return: 0 at all times
*/
int directory_change(info_t *info)
{
char *s, *dir, buffer[1024];
int chdir_ret;
s = getcwd(buffer, 1024);
if (!s)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
dir = _getenv(info, "HOME=");
if (!dir)
chdir_ret =
chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (strcmp_lexicogarphic(info->argv[1], "-") == 0)
{
if (!_getenv(info, "OLDPWD="))
{
_puts(s);
putchar_intiger('\n');
return (1);
}
_puts(_getenv(info, "OLDPWD=")), putchar_intiger('\n');
chdir_ret =
chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(info->argv[1]);
if (chdir_ret == -1)
{
error_printer(info, "can't cd to ");
eputs_voider(info->argv[1]), eputchar_intiger('\n');
}
else
{
env_setter(info, "OLDPWD", _getenv(info, "PWD="));
env_setter(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
* _assist - the current directory will be
* changed on the process
*
* @info: Structure having posible disagreement
* Used to control constant function framework.
*
* Return: 0 at all times
*/
int _assist(info_t *info)
{
char **arg_array;
arg_array = info->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array);
return (0);
}

