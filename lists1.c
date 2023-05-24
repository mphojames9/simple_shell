#include "shell.h"
/**
* list_len - factors length linked-list
* @h: pointer pointing towards first node
* Return: size-list checking
*/
size_t list_len(const list_t *h)
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
* to_the_strings_lister - bring array of strings to the list->str
* @head: pointer pointing towards first node
* Return: array of strings checking
*/
char **to_the_strings_lister(list_t *head)
{
list_t *node = head;
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
str = malloc(strlen_length(node->str) + 1);
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
* print_list - prints the overall elements in a list_t linked-list
* @h: pointer pontint towards first node
* Return: size of list checking
*/
size_t print_list(const list_t *h)
{
size_t i = 0;
while (h)
{
_puts(convert_number(h->num, 10, 0));
putchar_intiger(':');
putchar_intiger(' ');
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}
return (i);
}
/**
* node_starts_with - returns node with prefix start string
* @node: pointer pointing towards the list head
* @prefix: string to match-checked
* @c: the next character after prefix-match
* Return: match node or null as required
*/
list_t *node_starts_with(list_t *node, char *prefix, char c)
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
* get_node_index - index node retriever
* @head: pointer pointing towards list-head
* @node: pointer pointing towards the node
* Return: index at node or   -1
*/
ssize_t get_node_index(list_t *head, list_t *node)
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

