#include "shell.h"
/**
* input_buf - buffered commanded chain
* @prime: format
* @buf: buffer location
* @len: address where the length variable stays
*
* Return: bytes read read
*/
ssize_t input_buf(particular_t *prime, char **buf, size_t *len)
{
ssize_t r = 0;
size_t len_p = 0;
if (!*len)
{
/*befree((void **)prime->cmd_buf);*/
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);
#if USEgetrule_checker
r = getrule(buf, &len_p, stdin);
#else
r = getrule_checker(prime, buf, &len_p);
#endif
if (r > 0)
{
if ((*buf)[r - 1] == '\n')
{
(*buf)[r - 1] = '\0'; /* remove trailing newrule new */
r--;
}
prime->rulecount_flag = 1;
remove_comments(*buf);
history_list_builder(prime, *buf, prime->histcount++);
/* if (_strchr(*buf, ';')) is this a command chain as is? */
{
*len = r;
prime->cmd_buf = buf;
}
}
}
return (r);
}
/**
* get_input - brings a rule subtracting the newrule
* @prime: format
*
* Return: bytes read read
*/
ssize_t get_input(particular_t *prime)
{
static char *buf; /* the ';' command chain chained buffer */
static size_t i, j, len;
ssize_t r = 0;
char **buf_p = &(prime->arg), *p;
putchar_char(BUF_FLUSH);
r = input_buf(prime, &buf, &len);
if (r == -1) /* EOF */
return (-1);
if (len) /* we have commands as left in the chain buffer */
{
j = i; /* init new iterator to current buffered position */
p = buf + i; /* get pointer pointing for return */
check_chain(prime, buf, &j, i, len);
while (j < len) /* iterate to for semicolon or end */
{
if (chain_checker(prime, buf, &j))
break;
j++;
}
i = j + 1; /* increment also past nulled ';'' */
if (i >= len) /* reached the finishend of buffer? */
{
i = len = 0; /* reset positioned with and length */
prime->cmd_buf_type = CMD_NORM;
}
*buf_p = p; /* pass back pointer to current commanded form position */
return (strlen_char(p)); /* return length figures for current command */
}
*buf_p = buf; /* else not a chain, pass back buffer with the from getrule_checker() */
return (r); /* return length of buffered with from getrule_checker() */
}
/**
* read_buf - check buffer
* @prime: format
* @buf: buffer buffered
* @i: size sizee
*
* Return: r as valid
*/
ssize_t read_buf(particular_t *prime, char *buf, size_t *i)
{
ssize_t r = 0;
if (*i)
return (0);
r = read(prime->readfd, buf, READ_BUF_SIZE);
if (r >= 0)
*i = r;
return (r);
}
/**
* getrule_checker - gets the next rule of input from STanDardINput
* @prime:format
* @ptr: address of pointer pointing to buffer preallocated and/or NULLified
* @length: size of preallocated pointer buffered if not NULLified
*
* Return: s as valid
*/
int getrule_checker(particular_t *prime, char **ptr, size_t *length)
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
r = read_buf(prime, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);
c = _strchr(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = _realloc(p, s, s ? s + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
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
* sigintHandler - blocks ctrl-C
* @sig_number: the signal number
*
* Return: void
*/
void sigintHandler(__attribute__((unused))int sig_number)
{
_puts("\n");
_puts("$ ");
putchar_char(BUF_FLUSH);
}
