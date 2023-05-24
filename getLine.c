#include "shell.h"
/**
* input_buf - buffering of the chained command
* @info: format structure
* @buf: buffer location
* @len: lenght variable location
* Return: value of bytes read
*/
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
ssize_t r = 0;
size_t len_p = 0;
if (!*len) /* if the buffer is empty, make it full */
{
/*bsafer((void **)info->cmd_buf);*/
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);
#if USE_GETLINE
r = getline(buf, &len_p, stdin);
#else
r = _getline(info, buf, &len_p);
#endif
if (r > 0)
{
if ((*buf)[r - 1] == '\n')
{
(*buf)[r - 1] = '\0'; /* delete trailing newline */
r--;
}
info->linecount_flag = 1;
comments_remover(*buf);
history_builder_list(info, *buf, info->histcount++);
/* if (_strchr(*buf, ';')) command chain activated? */
{
*len = r;
info->cmd_buf = buf;
}
}
}
return (r);
}
/**
* get_input - newline not included in the line
* @info: format structure
* Return: value of bytes read
*/
ssize_t get_input(info_t *info)
{
static char *buf; /* the ';' command chain-buffer */
static size_t i, j, len;
ssize_t r = 0;
char **buf_p = &(info->arg), *p;
putchar_intiger(BUF_FLUSH);
r = input_buf(info, &buf, &len);
if (r == -1) /* EOF... */
return (-1);
if (len) /* we have commands available the chain buffer */
{
j = i; /* init new iterator to current buffering position */
p = buf + i; /* get pointer as return */
chain_inspect(info, buf, &j, i, len);
while (j < len) /* iterate into semicolon or end */
{
if (chain_checks(info, buf, &j))
break;
j++;
}
i = j + 1; /* increment over nulled ';'' */
if (i >= len) /*  end of buffer? */
{
i = len = 0; /* position and length to default */
info->cmd_buf_type = CMD_NORM;
}
*buf_p = p; /* reverse pointer to current command position */
return (strlen_length(p)); /* rev length of current command */
}
*buf_p = buf; /* if not chain, pass back buffer from _getline() */
return (r); /* reverse buffer length from _getline() */
}
/**
* read_buf - read  buffer
* @info: form structural
* @buf: buffer as seen
* @i: size of
* Return: r
*/
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
ssize_t r = 0;
if (*i)
return (0);
r = read(info->readfd, buf, READ_BUF_SIZE);
if (r >= 0)
*i = r;
return (r);
}
/**
* _getline - retrieve the furhter line of input from STDIN
* @info: format structure
* @ptr: pointer to buffer locator
* @length: preallocated size of pointer to buffer if different from NULL
* Return: s
*/
int _getline(info_t *info, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;
p = *ptr;
if (p && length)
s = *length;
if (i == len)
i = len = 0;
r = read_buf(info, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);
c = _strchr(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = relocator(p, s, s ? s + k : k + 1);
if (!new_p) /* MALLOC FAIL! */
return (p ? free(p), -1 : -1);
if (s)
_strncat(new_p, buf + i, k - i);
else
_strncpy(new_p, buf + i, k - i + 1);
s += k - i;
i = k;
p = new_p;
if (length)
*length = s;
*ptr = p;
return (s);
}
/**
* sigintHandler - impedes ctrl-C
* @sig_num: signalling number
* Return: void
*/
void sigintHandler(__attribute__ ((unused))int sig_num)
{
_puts("\n");
_puts("$ ");
putchar_intiger(BUF_FLUSH);
}

