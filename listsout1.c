#include "shell.h"
/**
* list_len - length of linked list to determine
*
* @h: first node pointer
*
* Return: list size
*/
size_t list_len(const record_m *h)
{
size_t i = 0;
while (h)
{
h = h->next;
i++;
}
return (i);
}
/**
* record_mo_strings - array of strings of the list->str is returned
*
* @head: pointer to first node
*
* Return: array of strings
*/
char **record_mo_strings(record_m *head)
{
record_m *node = head;
size_t i = list_len(head), j;
char **strs;
char *str;
if (!head || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));
if (!strs)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
str = malloc(strlen_char(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}
str = _strcpy(str, node->str);
strs[i] = str;
}
strs[i] = NULL;
return (strs);
}
/**
* print_list - elements of a record_m linked list are printed
*
* @h: first node pointer
*
* Return: list size
*/
size_t print_list(const record_m *h)
{
size_t i = 0;
while (h)
{
_puts(convert_number(h->num, 10, 0));
putchar_char(':');
putchar_char(' ');
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}
return (i);
}
/**
* node_starts_with - string starts with prefix is returned
*
* @node: list head poiter
* @prefix: matched string
* @c: character after prefix to be match
*
* Return: match node or null
*/
record_m *node_starts_with(record_m *node, char *prefix, char c)
{
char *p = NULL;
while (node)
{
p = starts_with(node->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}
/**
* get_node_index - index of a node
*
* @head: pointer to list head
* @node: pointer to the node
*
* Return: index of node or -1
*/
ssize_t get_node_index(record_m *head, record_m *node)
{
size_t i = 0;
while (head)
{
if (head == node)
return (i);
head = head->next;
i++;
}
return (-1);
}
