#include "shell.h"
/**
* cmd_checker - confirms file is an executable command or no
* @info: informational structural
* @path: directive to file
* Return: 1 if successful, then 0 if not
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
* dup_chars - character copying
* @pathstr: PATH for string
* @start: beginning  of index
* @stop: end of  index
* Return: pointer location for new buffer
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
* find_path - finds the exact command along PATH string
* @info: information structureral
* @pathstr: PATH string string
* @cmd: command finding
* Return: full path for command if found otherwise then NULL
*/
char *find_path(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;
if (!pathstr)
return (NULL);
if ((strlen_length(cmd) > 2) && starts_with(cmd, "./"))
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

