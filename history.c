#include "shell.h"
/**
* get_history_file - gets the history file
* @info: parameter struct
*
* Return: allocated string containg history file
*/
char *get_history_file(info_t *info)
{
char *buf, *dir;
dir = _getenv(info, "HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (strlen_char(dir) + strlen_char(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
_strcpy(buf, dir);
_strcat(buf, "/");
_strcat(buf, HIST_FILE);
return (buf);
}
/**
* history_writer - creates a file, or appends to an existing file
* @info: the parameter struct
*
* Return: 1 on success, else -1
*/
int history_writer(info_t *info)
{
ssize_t fd;
char *filename = get_history_file(info);
record_m *node = NULL;
if (!filename)
return (-1);
fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = info->history; node; node = node->next)
{
putsfd_char(node->str, fd);
putfd_char('\n', fd);
}
putfd_char(BUF_FLUSH, fd);
close(fd);
return (1);
}
/**
* history_reader - reads history from file
* @info: the parameter struct
*
* Return: histcount on success, 0 otherwise
*/
int history_reader(info_t *info)
{
int i, last = 0, linecount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = get_history_file(info);
if (!filename)
return (0);
fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fd);
for (i = 0; i < fsize; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
history_list_builder(info, buf + last, linecount++);
last = i + 1;
}
if (last != i)
history_list_builder(info, buf + last, linecount++);
free(buf);
info->histcount = linecount;
while (info->histcount-- >= HIST_MAX)
node_at_index_deletion(&(info->history), 0);
history_renumber(info);
return (info->histcount);
}
/**
* history_list_builder - adds entry to a history linked list
* @info: Structure containing potential arguments. Used to maintain
* @buf: buffer
* @linecount: the history linecount, histcount
*
* Return: Always 0
*/
int history_list_builder(info_t *info, char *buf, int linecount)
{
record_m *node = NULL;
if (info->history)
node = info->history;
add_node_end(&node, buf, linecount);
if (!info->history)
info->history = node;
return (0);
}
/**
* history_renumber - renumbers the history linked list after changes
* @info: Structure containing potential arguments. Used to maintain
*
* Return: the new histcount
*/
int history_renumber(info_t *info)
{
record_m *node = info->history;
int i = 0;
while (node)
{
node->num = i++;
node = node->next;
}
return (info->histcount = i);
}
