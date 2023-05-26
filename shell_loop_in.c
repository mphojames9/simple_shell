#include "shell.h"
/**
* hsh - shell loop
*
* @prime: treturn prime struct
* @av: vector from main disagreement
*
* Return: 0 on success, 1 on error
*/
int hsh(particular_t *prime, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;
while (r != -1 && builtin_ret != -2)
{
clear_prime(prime);
if (interactive_primer(prime))
_puts("$ ");
eputchar_chr(BUF_FLUSH);
r = get_input(prime);
if (r != -1)
{
set_prime(prime, av);
builtin_ret = builtin_locator(prime);
if (builtin_ret == -1)
find_cmd(prime);
}
else if (interactive_primer(prime))
putchar_char('\n');
free_prime(prime, 0);
}
history_writer(prime);
free_prime(prime, 1);
if (!interactive_primer(prime) && prime->status)
exit(prime->status);
if (builtin_ret == -2)
{
if (prime->err_num == -1)
exit(prime->status);
exit(prime->err_num);
}
return (builtin_ret);
}
/**
* builtin_locator - builtin command finder
*
* @prime: parameter & prime struct
*
* Return: -1 if builtin not found,
* 0 if builtin executed successfully,
* 1 if builtin found but not successful,
* 2 if builtin signals exit()
*/
int builtin_locator(particular_t *prime)
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
if (strcmp_char(prime->argv[0], builtintbl[i].type) == 0)
{
prime->line_count++;
built_in_ret = builtintbl[i].func(prime);
break;
}
return (built_in_ret);
}
/**
* find_cmd - command in PATH finder
* @prime: the parameter index
*
* Return: void
*/
void find_cmd(particular_t *prime)
{
char *path = NULL;
int i, k;
prime->path = prime->argv[0];
if (prime->linecount_flag == 1)
{
prime->line_count++;
prime->linecount_flag = 0;
}
for (i = 0, k = 0; prime->arg[i]; i++)
if (!delim_check(prime->arg[i], " \t\n"))
k++;
if (!k)
return;
path = find_path(prime, _getenv(prime, "PATH="), prime->argv[0]);
if (path)
{
prime->path = path;
fork_cmd(prime);
}
else
{
if ((interactive_primer(prime) || _getenv(prime, "PATH=")
|| prime->argv[0][0] == '/') && cmd_checker(prime, prime->argv[0]))
fork_cmd(prime);
else if (*(prime->arg) != '\n')
{
prime->status = 127;
print_error(prime, "not found\n");
}
}
}
/**
* fork_cmd - thread to run cmd forker
*
* @prime: the parameter
*
* Return: void
*/
void fork_cmd(particular_t *prime)
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
if (execve(prime->path, prime->argv, get_environ(prime)) == -1)
{
free_prime(prime, 1);
if (errno == EACCES)
exit(126);
exit(1);
}

}
else
{
wait(&(prime->status));
if (WIFEXITED(prime->status))
{
prime->status = WEXITSTATUS(prime->status);
if (prime->status == 126)
print_error(prime, "Permission denied\n");
}
}
}
