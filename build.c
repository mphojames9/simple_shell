#include "shell.h"
/**
* _myevacuate - leaves shell
* @prime: Structure with possible clash
* Return: exit as an exited stat
* (0) if prime.argv[0] != "exit"
*/
int _myevacuate(particular_t *prime)
{
int exitcheck;
if (prime->argv[1])
{
exitcheck = erratoi_check(prime->argv[1]);
if (exitcheck == -1)
{
prime->status = 2;
print_error(prime, "Illegal number: ");
_eputs(prime->argv[1]);
eputchar_chr('\n');
return (1);
}
prime->err_number = erratoi_check(prime->argv[1]);
return (-2);
}
prime->err_number = -1;
return (-2);
}
/**
* cd_change - gets the current directory into another
* @prime: Structure with possible clash
* Return: Always 0 when successful
*/
int cd_change(particular_t *prime)
{
char *s, *dir, buffer[1024];
int chdir_ret;
s = getcwd(buffer, 1024);
if (!s)
_puts("TO_DO: >>getcwd failure-msg here<<\n");
if (!prime->argv[1])
{
dir = _getenv(prime, "HOME=");
if (!dir)
chdir_ret =
chdir((dir = _getenv(prime, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (strcmp_char(prime->argv[1], "-") == 0)
{
if (!_getenv(prime, "OLDPWD="))
{
_puts(s);
putchar_char('\n');
return (1);
}
_puts(_getenv(prime, "OLDPWD=")), putchar_char('\n');
chdir_ret =
chdir((dir = _getenv(prime, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(prime->argv[1]);
if (chdir_ret == -1)
{
print_error(prime, "can't cd to ");
_eputs(prime->argv[1]), eputchar_chr('\n');
}
else
{
setenv2_checker(prime, "OLDPWD", _getenv(prime, "PWD="));
setenv2_checker(prime, "PWD", getcwd(buffer, 1024));
}
return (0);
}
/**
* _myassistance - reshuffle the working directory
* @prime: Structure with possible clash
* Return: Always 0 if successful completed
*/
int _myassistance(particular_t *prime)
{
char **arg_array;
arg_array = prime->argv;
_puts("help call works. Function not implemented \n");
if (0)
_puts(*arg_array);
return (0);
}
