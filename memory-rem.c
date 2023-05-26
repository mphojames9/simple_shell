#include "shell.h"

/**
 * befree - NULLifies the address to the location pointer is freed
 * @ptr: pointer's address that needs freeing
 * Return: 1 if succesfully, 0 om failer
 */
int befree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
