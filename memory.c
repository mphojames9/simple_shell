#include "shell.h"
/**
* bsafer - frees a pointer and NULLs the address
* @ptr: address of the pointer to free
*
* Return: 1 if freed, otherwise 0.
*/
int bsafer(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}
