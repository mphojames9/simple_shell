#include "shell.h"
/**
* bsafer - pointer reliever  and address NULLer
* @ptr: pointer address to be freed
* Return: 1 if freeing is succesful, then if not 0.
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
