#include "shell.h"
/**
* main - entry mode
* @ac: arg count counting
* @av: arg vector verctors
*
* Return: 0 on successful, then 1 on error
*/
int main(int ac, char **av)
{
info_t info[] = { INFO_INIT };
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
eputs_voider(av[0]);
eputs_voider(": 0: Can't open mode ");
eputs_voider(av[1]);
eputchar_intiger('\n');
eputchar_intiger(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
info->readfd = fd;
}
env_list_populator(info);
history_reader(info);
hsh_int(info, av);
return (EXIT_SUCCESS);
}
