#include "shell.h"
/**
* cmd_checker - executable command is determined
*
* @info: information struct
* @path: path to the file
*
* Return: 1 if true, 0 otherwise
*/
int cmd_checker(info_t *info, char *path)
{
struct stat st;
(void)info;
if (!path || stat(path, &st))
return (0);
if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}
/**
* dup_chars - characters are duplicated
* @pathstr: PATH string
* @start: index starting point
* @stop: index stoping
*
* Return: new buffer pointer
*/
char *dup_chars(char *pathstr, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;
for (k = 0, i = start; i < stop; i++)
if (pathstr[i] != ':')
buf[k++] = pathstr[i];
buf[k] = 0;
return (buf);
}
/**
* find_path - cmd in the PATH string is found
* @info: information struct
* @pathstr: the string PATH
* @cmd: find cmd
*
* Return: cmd if found or NULL
*/
char *find_path(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;
if (!pathstr)
return (NULL);
if ((strlen_char(cmd) > 2) && starts_with(cmd, "./"))
{
if (cmd_checker(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = dup_chars(pathstr, curr_pos, i);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (cmd_checker(info, path))
return (path);
if (!pathstr[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}
