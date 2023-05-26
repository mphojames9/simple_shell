#include "shell.h"
/**	
* add_node - node to the start of the list is added
* @head: address of pointer to head node
* @str: field of node srt
* @num: node index 
*
* Return: size of list
*/
record_m *add_node(record_m **head, const char *str, int num)
{
record_m *new_head;
if (!head)
return (NULL);
new_head = malloc(sizeof(record_m));
if (!new_head)
return (NULL);
_memset((void *)new_head, 0, sizeof(record_m));
new_head->num = num;
if (str)
{
new_head->str = _strdup(str);
if (!new_head->str)
{
free(new_head);
return (NULL);
}
}
new_head->next = *head;
*head = new_head;
return (new_head);
}
/**
* add_node_end - adds a node to the end of the list
* @head: address of pointer to head node
* @str: str field of node
* @num: node index used by history
*
* Return: size of list
*/
record_m *add_node_end(record_m **head, const char *str, int num)
{
record_m *new_node, *node;
if (!head)
return (NULL);
node = *head;
new_node = malloc(sizeof(record_m));
if (!new_node)
return (NULL);
_memset((void *)new_node, 0, sizeof(record_m));
new_node->num = num;
if (str)
{
new_node->str = _strdup(str);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}
if (node)
{
while (node->next)
node = node->next;
node->next = new_node;
}
else
*head = new_node;
return (new_node);
}
/**
* print_list_str - str element of a record_m linked list to be printed
* @h: first node first node
*
* Return: list size
*/
size_t print_list_str(const record_m *h)
{
size_t i = 0;
while (h)
{
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}
return (i);
}
/**
* node_at_index_deletion - delete given
* @head: pointer to 1st node
* @index: node to delete index
*
* Return: 1 success, 0 if else
*/
int node_at_index_deletion(record_m **head, unsigned int index)
{
record_m *node, *prev_node;
unsigned int i = 0;
if (!head || !*head)
return (0);
if (!index)
{
node = *head;
*head = (*head)->next;
free(node->str);
free(node);
return (1);
}
node = *head;
while (node)
{
if (i == index)
{
prev_node->next = node->next;
free(node->str);
free(node);
return (1);
}
i++;
prev_node = node;
node = node->next;
}
return (0);
}
/**
* untenanted_record - all nodes of a list are free
* @head_ptr: location of pointer to head node
*
* Return: void
*/
void untenanted_record(record_m **head_ptr)
{
record_m *node, *next_node, *head;
if (!head_ptr || !*head_ptr)
return; 
head = *head_ptr;
node = head;
while (node)
{
next_node = node->next;
free(node->str);
free(node);
node = next_node;
}
*head_ptr = NULL;
}
