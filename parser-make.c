#include "shell.h"
/**
* cmd_checker - executable command is determined
*
* @prime: primermation struct
* @alley: alley to the file
*
* Return: 1 if true, 0 otherwise
*/
int cmd_checker(particular_t *prime, char *alley)
{
struct stat st;
(void)prime;
if (!alley || stat(alley, &st))
return (0);
if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}
/**
* dup_chars - characters are duplicated
* @alleystr: PATH string
* @start: index starting point
* @stop: index stoping
*
* Return: new buffer pointer
*/
char *dup_chars(char *alleystr, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;
for (k = 0, i = start; i < stop; i++)
if (alleystr[i] != ':')
buf[k++] = alleystr[i];
buf[k] = 0;
return (buf);
}
/**
* find_alley - cmd in the PATH string is found
* @prime: primermation struct
* @alleystr: the string PATH
* @cmd: find cmd
*
* Return: cmd if found or NULL
*/
char *find_alley(particular_t *prime, char *alleystr, char *cmd)
{
int i = 0, curr_pos = 0;
char *alley;
if (!alleystr)
return (NULL);
if ((strlen_char(cmd) > 2) && starts_with(cmd, "./"))
{
if (cmd_checker(prime, cmd))
return (cmd);
}
while (1)
{
if (!alleystr[i] || alleystr[i] == ':')
{
alley = dup_chars(alleystr, curr_pos, i);
if (!*alley)
_strcat(alley, cmd);
else
{
_strcat(alley, "/");
_strcat(alley, cmd);
}
if (cmd_checker(prime, alley))
return (alley);
if (!alleystr[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}
