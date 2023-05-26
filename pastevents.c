#include "shell.h"
/**
* get_history_file - locates the past files
* @prime: format structure
*
* Return: string with the past event file
*/
char *get_history_file(particular_t *prime)
{
char *buf, *dir;
dir = _getenv(prime, "HOME=");
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
* history_writer - makes file or adds to an existing file
* @prime: format structure
*
* Return: 1 on successful, if not -1
*/
int history_writer(particular_t *prime)
{
ssize_t fd;
char *filename = get_history_file(prime);
record_m *node = NULL;
if (!filename)
return (-1);
fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = prime->history; node; node = node->next)
{
putsfd_char(node->str, fd);
putfd_char('\n', fd);
}
putfd_char(BUF_FLUSH, fd);
close(fd);
return (1);
}
/**
* history_reader - checks the past event files
* @prime: format structure
*
* Return: pastevent tally on successful, if not 0
*/
int history_reader(particular_t *prime)
{
int i, last = 0, linecount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = get_history_file(prime);
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
history_list_builder(prime, buf + last, linecount++);
last = i + 1;
}
if (last != i)
history_list_builder(prime, buf + last, linecount++);
free(buf);
prime->histcount = linecount;
while (prime->histcount-- >= HIST_MAX)
node_at_index_deletion(&(prime->history), 0);
history_renumberber(prime);
return (prime->histcount);
}
/**
* history_list_builder - additional to a pastevent linked list
* @prime: Structure with possible clash
* @buf: buffer buffer
* @linecount: pastevent line-count
*
* Return: Always 0
*/
int history_list_builder(particular_t *prime, char *buf, int linecount)
{
record_m *node = NULL;
if (prime->history)
node = prime->history;
add_node_end(&node, buf, linecount);
if (!prime->history)
prime->history = node;
return (0);
}
/**
* history_renumberber - give the pastevent linked list new numberbers when changed
* @prime: Structure containing potential arguments. Used to maintainwith possible clash
*
* Return: the current pastevent count
*/
int history_renumberber(particular_t *prime)
{
record_m *node = prime->history;
int i = 0;
while (node)
{
node->number = i++;
node = node->next;
}
return (prime->histcount = i);
}
