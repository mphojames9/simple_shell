#include "shell.h"
/**
* main - entry point
* @ac: arg count
* @av: arg vector
*	
* Return: 0 if successful, 1 on error
*/
int main(int ac, char **av)
{
particular_t prime[] = { INFO_INIT };
int fd = 2;
asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (fd)
: "r" (fd));
if (ac == 2)
{
fd = open(av[1], O_RDONLY);
if (fd == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
_eputs(av[0]);
_eputs(": 0: Can't open ");
_eputs(av[1]);
eputchar_chr('\n');
eputchar_chr(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
prime->readfd = fd;
}
env_list_population(prime);
history_reader(prime);
hsh(prime, av);
return (EXIT_SUCCESS);
}
